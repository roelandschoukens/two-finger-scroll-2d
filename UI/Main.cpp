#include "TouchDriver.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalTapSettingsForm.h"
#include "GlobalScrollSettingsForm.h"
#include "ApplicationSettingsForm.h"


#define MAX_LOG 5000

//==============================================================================
// this is just copied from juce\src\native\windows\juce_win32_messaging.cpp
class TwoFingerScroll2DApplication;

class HiddenMessageWindow
{
public:
    HiddenMessageWindow (const TCHAR* const messageWindowName, WNDPROC wndProc)
    {
        String className ("JUCE_");
        className << String::toHexString (Time::getHighResolutionTicks());

        HMODULE moduleHandle = (HMODULE) Process::getCurrentModuleInstanceHandle();

        WNDCLASSEX wc = { 0 };
        wc.cbSize         = sizeof (wc);
        wc.lpfnWndProc    = wndProc;
        wc.cbWndExtra     = 4;
        wc.hInstance      = moduleHandle;
        wc.lpszClassName  = className.toUTF16().getAddress();

        atom = RegisterClassEx (&wc);
        jassert (atom != 0);

        hwnd = CreateWindow (getClassNameFromAtom(), messageWindowName,
                             0, 0, 0, 0, 0, 0, 0, moduleHandle, 0);
        jassert (hwnd != 0);
    }

    ~HiddenMessageWindow()
    {
        DestroyWindow (hwnd);
        UnregisterClass (getClassNameFromAtom(), 0);
    }

    inline HWND getHWND() const noexcept     { return hwnd; }

private:
    ATOM atom;
    HWND hwnd;

    LPCTSTR getClassNameFromAtom() noexcept  { return (LPCTSTR) MAKELONG (atom, 0); }
};

class StandbyDetector
{
public:
	StandbyDetector (TwoFingerScroll2DApplication *app_) : 
		messageWindow (L"touchdriver_standbydetector", (WNDPROC) powerbroadcastCallback),
		app(app_)
    {
        SetWindowLongPtr (messageWindow.getHWND(), GWLP_USERDATA, (LONG_PTR) this);
    }

    virtual ~StandbyDetector() {}

    void powerEventDetected();

private:
    HiddenMessageWindow messageWindow;
	TwoFingerScroll2DApplication *app;

    static LRESULT CALLBACK powerbroadcastCallback (HWND h, const UINT message,
                                                       const WPARAM wParam, const LPARAM lParam)
    {
        if (message == WM_POWERBROADCAST)
        {
            ((StandbyDetector*) GetWindowLongPtr (h, GWLP_USERDATA))->powerEventDetected();
        }

        return DefWindowProc (h, message, wParam, lParam);
    }
};


class TwoFingerScroll2DApplication  : public JUCEApplication, 
									 public MouseListener,
									 public Timer,
									 public Logger
{

	class OurIconComponent : public SystemTrayIconComponent
	{
	public:
		OurIconComponent(TwoFingerScroll2DApplication *application) :
			app(application)
		{
			
		}


		virtual void mouseDown(const MouseEvent& e)
		{
			if (e.mods.isPopupMenu())
			{
				PopupMenu menu;
				menu.addItem(1, "Settings");
				menu.addItem(2, "About");
				menu.addItem(3, "Enabled", true, app->driver->isActive());
#ifdef DO_DEBUG_LOG
				menu.addItem(8, "Show debug log");
#endif
				menu.addItem(9, "Exit");
				int i = menu.show();
				switch (i)
				{
				case 1:
					app->showSettings("");
					break;
				case 2:
					app->showAbout();
					break;
				case 3:
					app->toggleActive();
					break;
#ifdef DO_DEBUG_LOG
				case 8:
					app->displayLog();
					break;
#endif
				case 9:
					app->quit();
					break;
				}
			}
			else
			{
				app->showSettings("");
			}
		}


		TwoFingerScroll2DApplication *app;


	};

public:

	TwoFingerScroll2DApplication() :
		settingsOpen(false),
		reattachCounter(0),
		logIndex(0)
    {
    }

    ~TwoFingerScroll2DApplication()
    {
    }

    
	void initialise (const String& commandLine)
    {
		Logger::setCurrentLogger(this);

		ttw = new TooltipWindow();
		icon = new OurIconComponent(this);
		Image img = ImageCache::getFromMemory(BinaryData::twofingerscroll2Ds_png, BinaryData::twofingerscroll2Ds_pngSize);
		icon->setIconImage(img);
		icon->setIconTooltip(getApplicationName());

		driver = new TouchPad::TouchDriver();
		standbyDetector = new StandbyDetector(this);
		
		icon->addMouseListener(this, false);

		LookAndFeel &laf = LookAndFeel::getDefaultLookAndFeel();
		Colour textColour = laf.findColour(AlertWindow::textColourId);
		laf.setColour(TabbedButtonBar::frontTextColourId,    textColour);
		laf.setColour(TabbedButtonBar::frontOutlineColourId, textColour);
		laf.setColour(TabbedButtonBar::tabTextColourId,      textColour.withAlpha(.9f));
		laf.setColour(TabbedButtonBar::tabOutlineColourId,   textColour.withAlpha(.9f));
		
		bool silent = (commandLine == String("/silent"));
		if (!silent)
		{
			showAbout();
		}
    }


	void showAbout()
	{
		AlertWindow::showMessageBox(AlertWindow::NoIcon, 
				APP_NAME,
				CharPointer_UTF8(
				u8"© 2017 by Roeland Schoukens\n\n"
				u8"Original two-finger-scroll by Arkadiusz Wahlig."));
	}


	void toggleActive()
	{
		if (driver->isActive())
		{
			driver->shutDown();
			Image img = ImageCache::getFromMemory(BinaryData::twofingerscroll2Dsoff_png, BinaryData::twofingerscroll2Dsoff_pngSize);
			icon->setIconImage(img);
		}
		else
		{
			driver = nullptr;
			driver = new TouchPad::TouchDriver();
			Image img = ImageCache::getFromMemory(BinaryData::twofingerscroll2Ds_png, BinaryData::twofingerscroll2Ds_pngSize);
			icon->setIconImage(img);
		}
	}


	void showSettings(const String &applicationName)
	{
		if (!settingsOpen)
		{
			settingsOpen = true;
			GlobalScrollSettingsForm form1(driver->getSettings());
			GlobalTapSettingsForm form2(driver->getSettings());
			ApplicationsettingsForm form3(applicationName);
			TabbedComponent tabs(TabbedButtonBar::TabsAtTop);
			int h = jmax(form1.getHeight(), form2.getHeight());
			h = jmax(h, form3.getHeight());
			tabs.setSize(form1.getWidth(), h + tabs.getTabBarDepth());
			Colour bgcolor = tabs.findColour(DocumentWindow::backgroundColourId);
			tabs.addTab(L"Scrolling", bgcolor, &form1, false);
			tabs.addTab(L"Actions", bgcolor, &form2, false);
			tabs.addTab(L"Applications", bgcolor, &form3, false);
			if (applicationName.isNotEmpty()) 
				tabs.getTabbedButtonBar().setCurrentTabIndex(2);
			DialogWindow::showModalDialog(getApplicationName(), &tabs, nullptr, bgcolor, true);
			TouchPad::saveSettings(driver->getSettings());
			if (TouchPad::gEditAppName.isNotEmpty())
			{
				TouchPad::saveAppSettings(TouchPad::gEditAppName, TouchPad::gEditSettings);
			}
			settingsOpen = false;
		}
		else
		{
			ModalComponentManager::getInstance()->bringModalComponentsToFront();
		}
	}


    void shutdown()
    {
		Logger::setCurrentLogger(nullptr);
    }


	void systemRequestedQuit()
    {
        quit();
    }

    
	const String getApplicationName()
    {
        return APP_NAME;
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return false;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
		bool silent = (commandLine == String("/silent"));
		if (!silent) {
			showAbout();
		}
    }

	void powerEventDetected()
	{
		if (reattachCounter == 0) {
			startTimer(3000);
		}
		reattachCounter = 20;
	}


	// --- implementation of Timer ---
	virtual void timerCallback()
	{
		driver->attachDeviceEvent();
		if (reattachCounter == 0) {
			stopTimer();
		} else {
			--reattachCounter;
		}
	}


	virtual void logMessage(const String &message)
	{
		log.set(logIndex, message);
		++logIndex;
		if (logIndex == MAX_LOG) logIndex = 0;
	}


#ifdef DO_DEBUG_LOG
	void displayLog()
	{
		Component c;
		int w = 300;
		int h = 0;
		for (int i = logIndex; i < log.size(); ++i) {
			Label *l = new Label(String::empty, log[i]);
			int lh = (int) ceil(l->getFont().getHeight());
			int lw = l->getFont().getStringWidth(log[i]);
			w = jmax(w, lw);
			l->setBounds(0, h, lw, lh);
			h += lh;
			c.addAndMakeVisible(l);
		}
		for (int i = 0; i < logIndex; ++i) {
			Label *l = new Label(String::empty, log[i]);
			int lh = (int) ceil(l->getFont().getHeight());
			int lw = l->getFont().getStringWidth(log[i]);
			w = jmax(w, lw);
			l->setBounds(0, h, lw, lh);
			h += lh;
			c.addAndMakeVisible(l);
		}
		DialogWindow::LaunchOptions dlo;
		c.setSize(w, h);
		Viewport v;
		v.setViewedComponent(&c, false);
		v.setSize(500, 400);
		dlo.content.setNonOwned(&v);
		v.setViewPosition(0, h);
		dlo.dialogTitle = CharPointer_UTF8(u8"Debug log — " APP_NAME);
		dlo.runModal();
		c.deleteAllChildren();
	}
#endif

private:
	ScopedPointer<TouchPad::TouchDriver> driver;
	ScopedPointer<StandbyDetector> standbyDetector;
	ScopedPointer<OurIconComponent> icon;
	ScopedPointer<TooltipWindow> ttw;
	unsigned int reattachCounter;
	bool settingsOpen;
	StringArray log;
	int logIndex;

};


void TouchPad::ShowSettingsMessage::messageCallback()
{
	TwoFingerScroll2DApplication *app = (TwoFingerScroll2DApplication*) JUCEApplication::getInstance();
	app->showSettings(appName);
}


void StandbyDetector::powerEventDetected()
{
	app->powerEventDetected();
}
START_JUCE_APPLICATION(TwoFingerScroll2DApplication)
