/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  21 Apr 2012 3:25:12pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_GLOBALSCROLLSETTINGSFORM_GLOBALSCROLLSETTINGSFORM_E4E0E9DF__
#define __JUCER_HEADER_GLOBALSCROLLSETTINGSFORM_GLOBALSCROLLSETTINGSFORM_E4E0E9DF__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
namespace TouchPad
{
	struct TouchSettings;
}
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GlobalScrollSettingsForm  : public Component,
                                  public SliderListener,
                                  public ComboBoxListener,
                                  public ButtonListener
{
public:
    //==============================================================================
    GlobalScrollSettingsForm (TouchPad::TouchSettings &settings_);
    ~GlobalScrollSettingsForm();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TouchPad::TouchSettings &settings;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* scrollGrp2;
    GroupComponent* scrollGrp;
    Label* label;
    Label* label2;
    Label* label7;
    Label* label5;
    Label* label3;
    Label* label4;
    Slider* xSpeedSlider;
    Slider* ySpeedSlider;
    Slider* xSnapSlider;
    Slider* ySnapSlider;
    ComboBox* scrollModeBox;
    Slider* momentumSlider;
    ToggleButton* intuitiveBtn;
    ToggleButton* accelerationBtn;
    Slider* accelerationSlider;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    GlobalScrollSettingsForm (const GlobalScrollSettingsForm&);
    const GlobalScrollSettingsForm& operator= (const GlobalScrollSettingsForm&);
};


#endif   // __JUCER_HEADER_GLOBALSCROLLSETTINGSFORM_GLOBALSCROLLSETTINGSFORM_E4E0E9DF__
