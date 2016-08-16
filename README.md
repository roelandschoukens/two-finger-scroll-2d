About
-----

This application replaces some of the functionality of the driver for Synaptics touchpads found on many laptops. This provides smooth 2-D scrolling with momentum, and three finger flicks.

This project is based on [two-finger-scroll](https://code.google.com/p/two-finger-scroll/) by Arkadiusz Wahlig.

two-finger-scroll has spawned a few other versions as well: [MacHater's version on tabletpcreview.com](http://forum.tabletpcreview.com/hp-touchsmart-tm2-wacom/38405-twofingerscroll-v1-0-7-update-two-finger-scrolling-done-right-more.html) and a version with  [2D scrolling and Windows 8 support](https://code.google.com/p/two-finger-scroll/issues/detail?id=19#c13)

Features
--------

 * Smooth scrolling in two dimensions with momentum;
 * Emulating mouse wheel clicks for applications which react badly to smooth scrolling;
 * 3-finger gestures to emulate the 'back' and 'forward' mouse buttons.

Using the app
-------------

  * In the synaptics control panel, **disable** any two-finger and three-finger gestures (pinch-zoom, two-finger scrolling, Application gestures).
  * Run the executable. A notification icon should appear, and you should be able to scroll with two fingers.
  * To run on startup you can add a shortcut to your Start menu » Startup folder, or add it to the registry. Add `/silent` as a command line argument to suppress the about dialog on startup.
  * to override settings for individual applications (many applications still react poorly to smooth scrolling), do a palm press gesture with that application in the foreground. If your touchpad doesn't recognise palm presses, assign "Show active app settings" to one of the other gestures.

Notes
-----

Old laptops may require more up-to-date drivers, check the [Synaptics web site](http://www.synaptics.com/resources/drivers).

To recognise 64-bit applications you need to run the 64-bit version. To recognise applications running with elevated rights you need to run this program as Administrator as well (But then you need to trust me, of course).

To work with applications running as *Administrator*, you have to run two-finger-scroll-2d as *Administrator* as well. But beware, this puts a lot of trust in both my good will and my programming skills.

I tested my version on a Dell XPS laptop (Windows 7 64-bit, and Windows 10) and on an old netbook (Which I believe is an OEM version of an MSI Wind U100, with 32-bit Windows XP). I don't know how well it works on other systems. If it doesn't work on your system, try one of the other projects mentioned above.

The settings are stored in the registry under `HKCU/Software/two-finger-scroll-2d`.

Building
--------

This project depends on the [JUCE library](http://www.juce.com/).

To build this project:

 * Download JUCE from [juce.com](http://www.juce.com/) or [GitHub](https://github.com/julianstorer/JUCE). When using the latter you'll have to build the `ProJucer` with one of the Visual Studio projects in `extras/Projucer/Builds`.

 * Start `ProJucer` and open `two-finger-scroll-2D.jucer`. Go to the *Config* tab and click *Save Project and Open in IDE…*. This should set up the project and open it in Visual Studio.
