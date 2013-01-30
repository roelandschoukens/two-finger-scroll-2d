#pragma once

#include "SynKit.h"
#include "TouchSettings.h"

inline void dprintf(TCHAR *pattern, ...)
{
	TCHAR buffer[1024];
	va_list vl;
	va_start(vl, pattern);
	wvsprintf(buffer, pattern, vl);
	va_end(vl);
	OutputDebugString(buffer);
}


#define APP_NAME "Two-finger-scroll-2D"

#define numKeyCodes 8

namespace TouchPad
{

class TouchDriver : public _ISynDeviceEvents,
	                     public Timer
{
public:
	TouchDriver();
	~TouchDriver() { shutDown(); }

	void shutDown();

	TouchSettings &getSettings() { return settings; }
	AppTouchSettings &getAppSettings() { return appSettings; }

	void UpdateForegroundWindowBaseModuleName();
	bool CheckDriver();

	ISynAPI *m_pAPI;
	ISynDevice *synTouchPad;
	ISynPacket *synPacket;

	bool isActive() { return working; }

	// reattach events (required after power state changes).
	void attachDeviceEvent();

	void scanKeyStates();
	bool rescanKeyStates();

	// timer callback
	virtual void timerCallback();

	// the packet callback
	virtual long STDMETHODCALLTYPE OnSynDevicePacket(long );

	// touchpad state helper methods
	void AcquirePad(bool acquire);
	void LockDeviceTap(bool lock);
	
	// mouse event constructors
	bool DoTap(int);
	bool DoScroll(long, long);
	void EndScrollGesture();
	void ResetScroll();
	bool DoScrollAxis(long dy, Axis axis, long dt);
	void fireScrollEvent(long d, Axis axis);

	// per app settings override
	void applyAppSettings();

	TouchSettings settings;
	AppTouchSettings appSettings;
	ScrollMode scrollMode;
	float scrollSpeed[2];

	// internal state
	long nof;
	bool working;

	bool swiping;

	long scrollTstamp;
	long scrollMomentum[2];
	SHORT keystates[numKeyCodes];

	long zPalmMin;
	bool palmDown;

	bool IsPadAcquired;
	bool synTapState;
	bool IsDeviceTapLocked;
	long tapLastNof;
	long tapStartTime, tapTouchTime, scrollTouchTime;
	long tapDistance;
	POINT tapTouchPos, scrollTouchPos;
	long scrollBuffer[2];
	long totalScroll[2];
	int scrollClamp;
	long scrollLastXDelta, scrollLastYDelta;
	bool scrollNotEdge;
};


} // end of namespace block
