// Original code from http://code.google.com/p/two-finger-scroll/

#include "TouchDriver.h"
#include "constants.h"
#include <Psapi.h>
#include <Shlwapi.h>
#include <cassert>

using namespace TouchPad;

struct TTapInfo {
	DWORD eventDown, eventUp, x;
};


static const TTapInfo tapInfo[] = {
	{0, 0, 0}, // disabled
	{MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP, 0},
	{MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP, 0},
	{MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP, 0},
	{MOUSEEVENTF_WHEEL, 0, (DWORD) -WHEEL_DELTA},
	{MOUSEEVENTF_WHEEL, 0, WHEEL_DELTA},
	{MOUSEEVENTF_HWHEEL, 0, (DWORD) -WHEEL_DELTA},
	{MOUSEEVENTF_HWHEEL, 0, WHEEL_DELTA},
	{MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP, XBUTTON1},
	{MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP, XBUTTON2}
};


static const int keyCodes[numKeyCodes] = {
    VK_LSHIFT,
    VK_RSHIFT,
    VK_LCONTROL,
    VK_RCONTROL,
    VK_LMENU,
    VK_RMENU,
    VK_LWIN,
    VK_RWIN };


static DWORD wheelFlags[2] = {MOUSEEVENTF_HWHEEL, MOUSEEVENTF_WHEEL};

// keep track of active application
static HWND activeHWnd = NULL;
static String activeWndName;

// Note: to get the application name for a 64-bit process, you need to run
// a 64-bit build.
// To get the name for an application running with admin rights, you need
// to run this as admin as well.
void TouchDriver::UpdateForegroundWindowBaseModuleName()
{
	HWND hWnd = GetForegroundWindow();

	if (hWnd != activeHWnd)
	{
		activeHWnd = hWnd;
		activeWndName = "";
		if (hWnd) {
			DWORD dwProcessId;
			HANDLE hProcess;

			GetWindowThreadProcessId(hWnd, &dwProcessId);
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ, false, dwProcessId);
			if (hProcess != NULL) {
				HMODULE hMod;
				DWORD cbNeeded;

				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
				{
					TCHAR name[MAX_PATH];
					GetModuleBaseName(hProcess, hMod, name, MAX_PATH);
					activeWndName = name;

					loadAppSettings(activeWndName, appSettings);
					applyAppSettings();
				}

				CloseHandle(hProcess);
			}
		}
	}
}


bool TouchDriver::CheckDriver()
{
	long multi = false;

	synTouchPad->GetProperty(SP_IsMultiFingerCapable, &multi);
	if (!multi) {
		HKEY key;
		LONG s = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Services\\SynTP\\Parameters", 0, KEY_READ, &key);
		if (s != ERROR_SUCCESS) {
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, APP_NAME,
				"Synaptics kernel driver registry keys missing. Reinstall drivers.");
			return false;
		}


		unsigned int val = 0;
		DWORD valSize = sizeof(val);
		DWORD valType;
		s = RegQueryValueEx(key, "CapabilitiesMask", NULL, &valType, (LPBYTE) &val, &valSize);
		if (s == ERROR_SUCCESS && valType == REG_DWORD && val == 0xFFFFFFFF) {
			RegCloseKey(key);
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, APP_NAME,
				"the driver still doesn't report multiple fingers. Either you haven't restarted\n"
				"the system yet or your TouchPad doesn't support multiple fingers.");
			return false;
		}
		if (val != 0xFFFFFFFF) {
			val = 0xFFFFFFFF;
			RegCloseKey(key);
			LONG s = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Services\\SynTP\\Parameters", 0, KEY_SET_VALUE, &key);
			if (s != ERROR_SUCCESS)
			{
				SHSetValue(key, NULL, "CapabilitiesMask", RRF_RT_REG_DWORD, &val, sizeof(val));
				RegCloseKey(key);
				AlertWindow::showMessageBox(AlertWindow::WarningIcon, APP_NAME,
						"Driver support for multiple fingers has been enabled.\n"
            			"\n"
						"Restart system for the changes to take effect.");
			}
			else
			{
				AlertWindow::showMessageBox(AlertWindow::WarningIcon, APP_NAME,
						"Driver support for multiple fingers is disabled, can't enable support.\n");
			}
			return false;
		}
		RegCloseKey(key);
	}
	return true;
}


TouchDriver::TouchDriver() :
	nof(0),
	working(false),
	IsDeviceTapLocked(false)
{
	loadSettings(settings);
	appSettings = gDefaultAppSettings;
	applyAppSettings();
	ResetScroll();

    long lHandle = -1;

	HRESULT hRes = CoInitialize(0);
    if (hRes && hRes != S_FALSE)
		return; // Error other than already initialized on thread.

    if (CoCreateInstance(_uuidof(SynAPI), 0, 
		 CLSCTX_INPROC_SERVER, _uuidof(ISynAPI), (void **) &m_pAPI) ||
      CoCreateInstance(_uuidof(SynPacket), 0, 
	     CLSCTX_INPROC_SERVER, _uuidof(ISynPacket), (void **) &synPacket) ||
      m_pAPI->Initialize() ||
      m_pAPI->FindDevice(SE_ConnectionAny, SE_DeviceTouchPad, &lHandle) || 
	  m_pAPI->CreateDevice(lHandle, &synTouchPad))
    {
      return; // Couldn't initialize properly.
    }

	synTouchPad->GetProperty(SP_ZMaximum, &zPalmMin);
	zPalmMin = zPalmMin * 2 / 3;

	attachDeviceEvent();
	working = true;
}


void TouchDriver::shutDown()
{
	if (isActive())
	{
		if (IsPadAcquired)
		{
			AcquirePad(false);
		}

		synTouchPad->Release();
		m_pAPI->Release();
		working = false;
	}
}


void TouchDriver::attachDeviceEvent()
{
	synTouchPad->SetSynchronousNotification(this);
}


// Hack to stop momentum when a modifier changes (so you don't start zooming
// in when you press Ctrl and the scroll momentum is still going). It doesn't
// work perfectly though, need to figure out how to do a proper keyboard hook.
void TouchDriver::scanKeyStates()
{
	for (int i = 0; i < numKeyCodes; ++i)
	{
		keystates[i] = GetKeyState(keyCodes[i]);
	}
}


bool TouchDriver::rescanKeyStates()
{
	bool changed = false;
	for (int i = 0; i < numKeyCodes; ++i)
	{
		SHORT old = keystates[i];
		keystates[i] = GetKeyState(keyCodes[i]);
		if (old != keystates[i]) changed = true;
	}
	return changed;
}


void TouchDriver::timerCallback()
{
	const static long FAST_FACTOR = 300;
	const static long SLOW_FACTOR = 5;

	bool hasmomentum = false;
	// stop momentum if shift states have changed.
	if (rescanKeyStates() == false)
	{
		for (int i = 0; i < 2; ++i) {
			if (scrollMomentum[i] != 0) {
				fireScrollEvent(scrollMomentum[i] / 40, (Axis) i);
				long drag = 100 - settings.scrollMomentum;
				long absM = abs(scrollMomentum[i]);
				absM = jmax(absM - SLOW_FACTOR * drag, 0L);   // mainly attenuates slow motion
				absM = absM * (FAST_FACTOR - drag) / FAST_FACTOR;   // mainly attenuates fast motion
				if (scrollMomentum[i] < 0) absM = -absM;
				scrollMomentum[i] = absM;
				hasmomentum = true;
			}
		}
	}
	if (!hasmomentum) { 
		stopTimer();
		ResetScroll();
	}
}


void TouchDriver::AcquirePad(bool acquire)
{
	if (acquire && !IsPadAcquired) {
		synTouchPad->Acquire(0);
		Logger::writeToLog("Pad acquired");
	}
	else if (!acquire && IsPadAcquired) {
		synTouchPad->Unacquire();
		Logger::writeToLog("Pad released");
	}
	IsPadAcquired = acquire;
}


void TouchDriver::LockDeviceTap(bool lock)
{
	long gest;

	if (lock != IsDeviceTapLocked) {
		if (lock) {
			synTouchPad->GetProperty(SP_Gestures, &gest);
			if (gest & SF_GestureTap) {
				synTouchPad->SetProperty(SP_Gestures, gest & (~SF_GestureTap));
				Logger::writeToLog("Tapping off");
				synTapState = true;
			}
			else synTapState = false;
		}
		else {
			synTouchPad->GetProperty(SP_Gestures, &gest);
			if (synTapState) gest |= SF_GestureTap;
			else gest &= ~SF_GestureTap;
			synTouchPad->SetProperty(SP_Gestures, gest);
			Logger::writeToLog(String("Tapping default"));
		}
		IsDeviceTapLocked = lock;
	}
}



long STDMETHODCALLTYPE TouchDriver::OnSynDevicePacket(long )
{
	long fstate, xd, yd;

	UpdateForegroundWindowBaseModuleName();

	// get the pointing data packet
	synTouchPad->LoadPacket(synPacket);

	// extract relevant data
	synPacket->GetProperty(SP_ExtraFingerState, &nof);
	nof &= 3;
	synPacket->GetProperty(SP_FingerState, &fstate);
	synPacket->GetProperty(SP_XDelta, &xd);
	synPacket->GetProperty(SP_YDelta, &yd);
	
	// handle tapping
	
	if (nof > tapLastNof) {
		// reset momentum on finger down
		scrollMomentum[0] = 0;
		scrollMomentum[1] = 0;

		if (nof >= 2) {
			synPacket->GetProperty(SP_TimeStamp,
				&tapStartTime);
			tapDistance = 0;
			LockDeviceTap(true);
		}
		if (tapLastNof == 0) {
			synPacket->GetProperty(SP_TimeStamp,
				&tapTouchTime);
			GetCursorPos(&tapTouchPos);
		}
	}
	else if (nof < tapLastNof) {
		if ((tapDistance < settings.tapMaxDistance) &&
			(tapLastNof >= 2))
		{
			bool ok = false;
			long tstamp;
			synPacket->GetProperty(SP_TimeStamp, &tstamp);
			if (tstamp - tapTouchTime < 175) {
				if (tapLastNof == 2)
					ok = DoTap(settings.tapTwo);
				else if (tapLastNof == 3)
					ok = DoTap(settings.tapThree);
			}
			else if (tstamp - tapStartTime < 175) {
				if (tapLastNof == 2)
					ok = DoTap(settings.tapOneOne);
				else if (tapLastNof == 3)
					ok = DoTap(settings.tapTwoOne);
			}
			if (ok)
				SetCursorPos(tapTouchPos.x, tapTouchPos.y);

			// prevent tap trigger until initiated again
			tapStartTime -= 175;
			tapLastNof = nof;
			return 0;
		}
	}
	if (IsDeviceTapLocked) {
		if (abs(xd) < 800) tapDistance += abs(xd);
		if (abs(yd) < 800) tapDistance += abs(yd);
		if (!(fstate & SF_FingerPresent))
			LockDeviceTap(false);
	}
	tapLastNof = nof;

	
	// handle swipe gestures
	
	if (nof >= 3 && !swiping)
	{
		// start swipe gestures on sufficient speed with 3 fingers
		int d = 0;
		if (abs(xd) < 800) d += abs(xd);
		if (abs(yd) < 800) d += abs(yd);
		if (d > settings.tapMaxDistance)
		{
			swiping = true;

			// do the action immediately, and eat all events until all fingers are gone, so if the
			// user swipes off the pad, there are no spurious scroll events.
			if (3 * abs(xd) > 4 * abs(yd))
			{
				DoTap(settings.swipe3[xd < 0 ? D_Left : D_Right]);
			}
			else if (3 * abs(yd) > 4 * abs(xd))
			{
				DoTap(settings.swipe3[yd < 0 ? D_Down : D_Up]);
			}

			if (!IsPadAcquired) {
				AcquirePad(true);
			}
		}
	}

	// detect palm press
	if (palmDown)
	{
		if (nof == 0)
		{
			palmDown = false;
		}
	}
	else if (nof == 1)
	{
		long z;
		synPacket->GetProperty(SP_Z, &z);
		if (z > zPalmMin)
		{ 
			palmDown = true;
			DoTap(settings.palm);
		}
	}

	
	if (swiping)
	{
		// keep swiping until all fingers are gone.
		if (nof == 0)
		{
			AcquirePad(false);
			swiping = false;
		}
	}


	// handle scrolling

	if (!swiping && settings.scrollLinear) {
		if (fstate & SF_FingerPresent) {
			if (scrollTouchTime == 0) {
				GetCursorPos(&scrollTouchPos);
				synPacket->GetProperty(SP_TimeStamp,
						&scrollTouchTime);
			}
			if (nof == 2) {
				long y, ylo, yhi;
				synPacket->GetProperty(SP_Y, &y);
				synTouchPad->GetProperty(SP_YLoBorder, &ylo);
				synTouchPad->GetProperty(SP_YHiBorder, &yhi);
				if (IsPadAcquired) {
					if (ylo <= y && y <= yhi && settings.scrollLinearEdge) {
						scrollNotEdge = true;
					}
					else if (scrollNotEdge && ((y < ylo && scrollLastYDelta < 0) ||
							(y > yhi && scrollLastYDelta > 0))) {
						DoScroll(scrollLastXDelta, scrollLastYDelta);
						return 0;
					}
				}
				if (fstate & SF_FingerMotion) {
					if (!IsPadAcquired) {
						AcquirePad(true);
						long tstamp;
						synPacket->GetProperty(SP_TimeStamp, &tstamp);

						// stop momentum if there is manual scroll movement
						stopTimer();

						if (tstamp - scrollTouchTime < 1000) {
							SetCursorPos(scrollTouchPos.x,
								scrollTouchPos.y);
						}
					}
					if (IsPadAcquired) {
						DoScroll(xd, yd);
						scrollLastXDelta = xd;
						scrollLastYDelta = yd;
					}
				} else {
					// reset momentum when fingers are not moving
					scrollMomentum[0] = 0;
					scrollMomentum[1] = 0;
				}
			}
			else {
				AcquirePad(false);
				// reset scroll + momentum when one or three fingers and not moving
				EndScrollGesture();
			}
		}
		else {
			AcquirePad(false);
			scrollTouchTime = 0;
			EndScrollGesture();
		}
	}

	return 0;
}


void TouchDriver::EndScrollGesture()
{
	if (scrollTstamp != 0) {
		if (scrollMomentum[0] != 0 || scrollMomentum[1] != 0) {
			startTimer(25);
			scanKeyStates();
		} else {
			ResetScroll();
		}
	}
	scrollTstamp = 0;
}


void TouchDriver::ResetScroll()
{
	scrollLastXDelta = scrollLastYDelta = 0;
	scrollBuffer[0] = 0;
	scrollBuffer[1] = 0;
	totalScroll[0] = 0;
	totalScroll[1] = 0;
	scrollClamp = 0;
	scrollMomentum[0] = 0;
	scrollMomentum[1] = 0;
	scrollNotEdge = false;
}


bool TouchDriver::DoTap(int index)
{
	if (index == TA_Settings)
	{
		fireAppSettingsMessage(activeWndName);
		return true;
	}
	else
	{
		INPUT i[2];
		const TTapInfo *info = &tapInfo[index];

		if (info->eventDown == 0) return false; // tapping disabled

		ZeroMemory(i, sizeof(INPUT)*2);
		i[0].type = INPUT_MOUSE;
		i[0].mi.dwFlags = info->eventDown;
		i[0].mi.mouseData = info->x;
		if (info->eventUp != 0)
		{
			i[1].type = INPUT_MOUSE;
			i[1].mi.dwFlags = info->eventUp;
			i[1].mi.mouseData = info->x;
		}
		SendInput(info->eventUp == 0 ? 1 : 2, i, sizeof(INPUT));
		return true;
	}
}
//---------------------------------------------------------------------------


bool TouchDriver::DoScroll(long dx, long dy)
{

	if (scrollClamp == 0)
	{
		if (abs(totalScroll[AXIS_X]) > WHEEL_DELTA && abs(totalScroll[AXIS_Y]) < settings.scrollSnap[AXIS_X])
		{
			scrollClamp = 2; // do X only
			scrollMomentum[AXIS_Y] = 0;
		}
		else if (abs(totalScroll[AXIS_Y]) > WHEEL_DELTA && abs(totalScroll[AXIS_X]) < settings.scrollSnap[AXIS_Y])
		{
			scrollClamp = 1; // do Y only
			scrollMomentum[AXIS_X] = 0;
		}
		else if (abs(totalScroll[AXIS_Y]) > WHEEL_DELTA && abs(totalScroll[AXIS_X]) > WHEEL_DELTA)
		{
			scrollClamp = 3; // do free 2-D scroll
		}
	}

	long dt;
	long lastT = scrollTstamp;
	synPacket->GetProperty(SP_TimeStamp, &scrollTstamp);
	dt = scrollTstamp - lastT;

	return (scrollClamp == 1 || DoScrollAxis(dx, AXIS_X, dt))
		&  (scrollClamp == 2 || DoScrollAxis(dy, AXIS_Y, dt));
}

// constants used for momentum. M_LAMBDA_MS * M_SCALE = 1000
#define M_LAMBDA_MS 100
#define M_SCALE 10

// momentum is expressed in units per second (where 1 wheel click is 120 units a.k.a. WHEEL_DELTA.
// time measurements come in milliseconds, hence the number 1000.

// the formula is a simple low pass filter:
//  v = 1000*d/dt
//  a = dt / lambda
//  M = M*(1 - a) + v*a
//    = M*(1 - dt / lambda) + 1000*d/lambda
//    = M*(lambda - dt)/lambda + d*(1000/lambda)

bool TouchDriver::DoScrollAxis(long dRaw, Axis axis, long dt)
{
	long d;

	if (settings.scrollIntuitive) dRaw = -dRaw;

	if (abs(dRaw) > 800)
		return false;

	// scrollSpeed
	dRaw = (long) ceil(dRaw * scrollSpeed[axis]);

	// scrollAcc
	if (settings.scrollAcc) {
		d = abs(dRaw) * (abs(dRaw) + settings.scrollAcc) / settings.scrollAcc;

		if (dRaw < 0)
			d = -d;
	}
	else d = dRaw;

	totalScroll[axis] += d;
	if (settings.scrollMomentum) {
		dt = jmin(dt, 1000L);
		scrollMomentum[axis] = scrollMomentum[axis] * (M_LAMBDA_MS - dt) / M_LAMBDA_MS + d * M_SCALE;
	}

	fireScrollEvent(d, axis);
	
	return true;
}


void TouchDriver::fireScrollEvent(long d, Axis axis)
{
	if (scrollMode == S_Discrete) {
		long delta = WHEEL_DELTA;
		scrollBuffer[axis] += d;
		d = scrollBuffer[axis] - scrollBuffer[axis] % delta;
	}

	if (d != 0) {
		INPUT i;

		ZeroMemory(&i, sizeof(INPUT));
		i.type = INPUT_MOUSE;
		i.mi.dwFlags = wheelFlags[axis];
		i.mi.mouseData = d;
		SendInput(1, &i, sizeof(INPUT));

		if (scrollMode == S_Discrete)
			scrollBuffer[axis] -= d;
	}
}


void TouchDriver::applyAppSettings()
{
	if (appSettings.scrollMode == S_Inherit)
	{
		scrollMode = settings.scrollMode;
	}
	else
	{
		scrollMode = appSettings.scrollMode;
	}

	for (int i = 0; i < 2; ++i)
	{
		scrollSpeed[i] = (settings.scrollSpeed[i] + 20)*appSettings.scrollSpeed[i]*.0002f;
		scrollSpeed[i] *= scrollSpeed[i];
	}
}
