// License: See note in TouchDriver.cpp

#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>
#include "touchSettings.h"

#define OUR_KEY "two-finger-scroll-2d"
#define HKCU "HKEY_CURRENT_USER\\"
static String globalKey = "Software\\" OUR_KEY "\\global";
static String appKey = "Software\\" OUR_KEY "\\apps";


const wchar_t *TouchPad::tapNames[TA_TAEnd] = {
	L"None",
	L"Left click",
	L"Middle click",
	L"Right click",
	L"Scroll down",
	L"Scroll up",
	L"Scroll left",
	L"Scroll right",
	L"Extra 1 (back)",
	L"Extra 2 (forward)",
	L"Show active app settings"
};


static DWORD getRegValue(const String &name, const String &valueName, DWORD defaultValue)
{
	MemoryBlock block;
	DWORD type = WindowsRegistry::getBinaryValue(HKCU + name+"\\"+valueName, block);
	if (type == REG_DWORD)
	{
		return (*(DWORD*) block.getData());
	}
	else
	{
		return defaultValue;
	}
}


static bool getRegBool(const String &name, const String &valueName, bool defaultValue)
{
	return getRegValue(name, valueName, defaultValue) != 0;
}


static void setRegValue(const String &name, const String &valueName, DWORD value)
{
	WindowsRegistry::setValue(HKCU + name+"\\"+valueName, (juce::uint32) value);
}


static void deleteRegValue(const String &name, const String &valueName)
{
	WindowsRegistry::deleteValue(HKCU + name+"\\"+valueName);
}


static void setRegValue(const String &name, const String &valueName, DWORD value, DWORD defaultValue)
{
	if (value == defaultValue)
		deleteRegValue(name, valueName);
	else
		setRegValue(name, valueName, value);
}


StringArray TouchPad::enumApplications()
{
	StringArray apps;

    HKEY rootKey = HKEY_CURRENT_USER;
	HKEY key;

	if (RegOpenKeyEx (rootKey, appKey.toUTF16().getAddress(), 0, KEY_READ, &key) == ERROR_SUCCESS)
	{
		LONG error = ERROR_SUCCESS;
		TCHAR name[256];
		for (DWORD index = 0; ; ++index)
		{
			DWORD nameSize = 256;
			error = RegEnumKeyEx(
					key,
					index,
					name,
					&nameSize,
					NULL,
					NULL,
					NULL,
					NULL
				);
			if (error == ERROR_SUCCESS)
			{
				String s = CharPointer_UTF16(name);
				apps.add(s);
			}
			else
			{
				break;
			}
		}

		RegCloseKey (key);
	}
	return apps;
}


namespace TouchPad
{

void saveSettings(TouchSettings &settings)
{
	setRegValue(globalKey, "tap2", settings.tapTwo);
	setRegValue(globalKey, "tap3", settings.tapThree);
	setRegValue(globalKey, "tap11", settings.tapOneOne);
	setRegValue(globalKey, "tap21", settings.tapTwoOne);
	setRegValue(globalKey, "swipe-left", settings.swipe3[D_Left]);
	setRegValue(globalKey, "swipe-right", settings.swipe3[D_Right]);
	setRegValue(globalKey, "swipe-up", settings.swipe3[D_Up]);
	setRegValue(globalKey, "swipe-down", settings.swipe3[D_Down]);
	setRegValue(globalKey, "palm", settings.palm);

	setRegValue(globalKey, "scroll-mode", settings.scrollMode);
	setRegValue(globalKey, "scroll-speed-x", settings.scrollSpeed[0]);
	setRegValue(globalKey, "scroll-speed-y", settings.scrollSpeed[1]);
	setRegValue(globalKey, "scroll-acceleration", settings.scrollAcc);
	setRegValue(globalKey, "scroll-momentum", settings.scrollMomentum);
	setRegValue(globalKey, "scroll-snap-x", settings.scrollSnap[0]);
	setRegValue(globalKey, "scroll-snap-y", settings.scrollSnap[1]);
	setRegValue(globalKey, "scroll-intuitive", settings.scrollIntuitive);
}

void loadSettings(TouchSettings &settings)
{
	settings.tapMaxDistance = 50;

	settings.tapTwo = getRegValue(globalKey, "tap2", TA_Middle);
	settings.tapThree = getRegValue(globalKey, "tap3", TA_Right);
	settings.tapOneOne = getRegValue(globalKey, "tap11", TA_None);
	settings.tapTwoOne = getRegValue(globalKey, "tap21", TA_None);
	settings.swipe3[D_Up] = getRegValue(globalKey, "swipe-up", TA_ScrollUp);
	settings.swipe3[D_Left] = getRegValue(globalKey, "swipe-left", TA_Back);
	settings.swipe3[D_Down] = getRegValue(globalKey, "swipe-down", TA_ScrollDown);
	settings.swipe3[D_Right] = getRegValue(globalKey, "swipe-right", TA_Forward);
	settings.palm = getRegValue(globalKey, "palm", TA_Settings);
	
	settings.scrollMode = (ScrollMode) getRegValue(globalKey, "scroll-mode", S_Smooth);
	settings.scrollSpeed[0] = getRegValue(globalKey, "scroll-speed-x", 40);
	settings.scrollSpeed[1] = getRegValue(globalKey, "scroll-speed-y", 40);
	settings.scrollAcc = getRegValue(globalKey, "scroll-acceleration", 75);
	settings.scrollMomentum = getRegValue(globalKey, "scroll-momentum", 80);
	settings.scrollSnap[0] = getRegValue(globalKey, "scroll-snap-x", WHEEL_DELTA / 6);
	settings.scrollSnap[1] = getRegValue(globalKey, "scroll-snap-y", WHEEL_DELTA / 6);
	settings.scrollLinear = getRegBool(globalKey, "scroll-linear", true);
	settings.scrollLinearEdge = getRegBool(globalKey, "scroll-linear-edge", false);
	settings.scrollIntuitive = getRegBool(globalKey, "scroll-intuitive", false);
}

// the application settings currently being edited if applicable
String gEditAppName;
AppTouchSettings gEditSettings;

const AppTouchSettings gDefaultAppSettings = {
	S_Inherit,  // mode
	S_X_Standard,  // x mode
	{50, 50}    // speed
};

void fireAppSettingsMessage(const String &appName)
{
	(new ShowSettingsMessage(appName))->post();
}

void saveAppSettings(const String &appName, AppTouchSettings &settings)
{
	String ourKey = String(appKey) + "\\" + appName;
	if (settings == gDefaultAppSettings)
	{
		WindowsRegistry::deleteKey(ourKey);
	}
	else
	{
		setRegValue(ourKey, "scroll-mode", settings.scrollMode, gDefaultAppSettings.scrollMode);
		setRegValue(ourKey, "x-scroll-mode", settings.xScrollMode, gDefaultAppSettings.xScrollMode);
		setRegValue(ourKey, "scroll-speed-x", settings.scrollSpeed[AXIS_X], gDefaultAppSettings.scrollSpeed[AXIS_X]);
		setRegValue(ourKey, "scroll-speed-y", settings.scrollSpeed[AXIS_Y], gDefaultAppSettings.scrollSpeed[AXIS_Y]);
		setRegValue(ourKey, "discrete-zoom", (DWORD) settings.discreteZoom, (DWORD) gDefaultAppSettings.discreteZoom);
	}
}


void loadAppSettings(const String &appName, AppTouchSettings &settings)
{
	if (appName == gEditAppName) {
		// if the applicatin settings dialog is open the registry still contains the old
		// settings.
		settings = gEditSettings;
	} else {
		String ourKey = appKey + "\\" + appName;
		settings.scrollMode = (ScrollMode) getRegValue(ourKey, "scroll-mode", gDefaultAppSettings.scrollMode);
		settings.xScrollMode = (XScrollMode) getRegValue(ourKey, "x-scroll-mode", gDefaultAppSettings.xScrollMode);
		settings.scrollSpeed[AXIS_X] = (ScrollMode) getRegValue(ourKey, "scroll-speed-x", gDefaultAppSettings.scrollSpeed[AXIS_X]);
		settings.scrollSpeed[AXIS_Y] = (ScrollMode)getRegValue(ourKey, "scroll-speed-y", gDefaultAppSettings.scrollSpeed[AXIS_Y]);
		settings.discreteZoom = (bool) getRegValue(ourKey, "discrete-zoom", (DWORD) gDefaultAppSettings.discreteZoom);
	}
}

} // end namespace