/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  8 Nov 2012 9:19:54pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_APPLICATIONSETTINGSFORM_APPLICATIONSETTINGSFORM_534537FC__
#define __JUCER_HEADER_APPLICATIONSETTINGSFORM_APPLICATIONSETTINGSFORM_534537FC__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
namespace TouchPad
{
	struct AppTouchSettings;
}
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ApplicationsettingsForm  : public Component,
                                 public ComboBoxListener,
                                 public SliderListener
{
public:
    //==============================================================================
    ApplicationsettingsForm (const String &appName);
    ~ApplicationsettingsForm();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void loadSettings();
    //[/UserVariables]

    //==============================================================================
    GroupComponent* scrollGrp;
    Label* label5;
    ComboBox* scrollModeBox;
    Slider* xSpeedSlider;
    Label* label2;
    Slider* ySpeedSlider;
    Label* label3;
    ComboBox* appCombo;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApplicationsettingsForm);
};


#endif   // __JUCER_HEADER_APPLICATIONSETTINGSFORM_APPLICATIONSETTINGSFORM_534537FC__
