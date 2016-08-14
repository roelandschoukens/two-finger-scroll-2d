// License: See note in TouchDriver.cpp

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace TouchPad
{

typedef unsigned int ActionId;


enum TapActions
{
	TA_None, TA_Left, TA_Middle, TA_Right, TA_ScrollDown, TA_ScrollUp, TA_ScrollLeft, TA_ScrollRight, TA_Back, TA_Forward, TA_Settings, 
	// invalid number = last valid number + 1
	TA_TAEnd
};

extern const wchar_t *tapNames[TA_TAEnd];

enum Direction
{
	D_Up, D_Right, D_Down, D_Left
};

enum Axis
{
	AXIS_X, AXIS_Y
};


enum ScrollMode
{
	S_Inherit, S_Smooth, S_Discrete
};

enum XScrollMode
{
	S_X_Standard, S_X_ShiftY
};

struct TouchSettings
{
	int tapMaxDistance;

	ActionId tapTwo;
	ActionId tapThree;
	ActionId tapOneOne;
	ActionId tapTwoOne;
	ActionId swipe3[4];
	ActionId palm;

	ScrollMode scrollMode;
	int scrollSpeed[2]; // 0 -- 100
	int scrollSnap[2];  // 0 -- WHEEL_DELTA (45°)
	int scrollMomentum; // 0 (off) -- 100 (coast)
	int scrollAcc;      // 120 (slow) -- 30 (fast), 0 (off)
	bool scrollLinear;
	bool scrollLinearEdge;
	bool scrollIntuitive;
};


struct AppTouchSettings
{
	ScrollMode scrollMode;
	XScrollMode xScrollMode;
	int scrollSpeed[2]; // -100 -- 100 (correction factor)
};

void saveSettings(TouchSettings &settings);
void loadSettings(TouchSettings &settings);

inline bool operator==(const AppTouchSettings &a, const AppTouchSettings &b)
{
	return memcmp(&a, &b, sizeof(a)) == 0;
}

void fireAppSettingsMessage(const String &appName);
void showSettingsCallback();
void saveAppSettings(const String &appName, AppTouchSettings &settings);
void loadAppSettings(const String &appName, AppTouchSettings &settings);

StringArray enumApplications();

extern String gEditAppName;
extern AppTouchSettings gEditSettings;
extern const AppTouchSettings gDefaultAppSettings;

class ShowSettingsMessage : public CallbackMessage
{
public:
	ShowSettingsMessage(String appName_)
	  : appName(appName_)
	{}
	virtual void messageCallback();
private:
	String appName;
};

} // end namespace
