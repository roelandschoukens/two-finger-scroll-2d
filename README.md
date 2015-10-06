This is Two-finger-scroll 2D, based on the [two-finger-scroll project](https://code.google.com/p/two-finger-scroll/) by Arkadiusz Wahlig.

two-finger-scroll has spawned a few other versions as well: 
[`MacHater`'s version](http://forum.tabletpcreview.com/hp-touchsmart-tm2-wacom/38405-twofingerscroll-v1-0-7-update-two-finger-scrolling-done-right-more.html) on tabletpcreview.com
and [a version with 2D scrolling and Windows 8 support](https://code.google.com/p/two-finger-scroll/issues/detail?id=19#c13)

Getting started
---------------

 - In the synaptics control panel, disable any two-finger and three-finger gestures (pinch-zoom, two-finger scrolling, Application gestures).
 - Run the executable. A notification icon should appear, and you should be able to scroll with two fingers.
 - To run on startup you can add a shortcut to your Start menu » Startup folder, or add it to the registry. Add /silent to the command line argument to suppress the about dialog on startup.
 - to override settings for individual applications (many applications still react poorly to smooth scrolling), do a palm press gesture with that application in the foreground. If your touchpad doesn't recognise palm presses, assign "Show active app settings" to one of the other gestures. 

Notes
-----

Old laptops may require more up-to-date drivers, check the Synaptics web site.

To recognise 64-bit applications you need to run the 64-bit version. To recognise applications running with elevated rights you need to run this program as Administrator as well (But then you need to trust me, of course).

I tested my version on a Dell XPS laptop (Windows 7 64-bit) and on an old netbook (Which I believe is an OEM version of an MSI Wind U100, with 32-bit Windows XP). I don't know how well it works on other systems. If it doesn't work on your system, try one of the other projects mentioned above.

The settings are stored in the registry under HKCU/Software/two-finger-scroll-2d.

Building
--------

To build this project you have to get a copy of the [JUCE library](http://www.juce.com/). It has a tool called the `IntroJucer`,
use it to open `two-finger-scroll-2D.jucer` and generate the appropriate build files.
