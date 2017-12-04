/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

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

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TouchPad::TouchSettings &settings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> scrollGrp2;
    ScopedPointer<GroupComponent> scrollGrp;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Slider> xSpeedSlider;
    ScopedPointer<Slider> ySpeedSlider;
    ScopedPointer<Slider> xSnapSlider;
    ScopedPointer<Slider> ySnapSlider;
    ScopedPointer<ComboBox> scrollModeBox;
    ScopedPointer<Slider> momentumSlider;
    ScopedPointer<ToggleButton> intuitiveBtn;
    ScopedPointer<ToggleButton> accelerationBtn;
    ScopedPointer<Slider> accelerationSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalScrollSettingsForm)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
