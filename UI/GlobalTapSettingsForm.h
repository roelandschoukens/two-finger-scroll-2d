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
class GlobalTapSettingsForm  : public Component,
                               public ComboBoxListener
{
public:
    //==============================================================================
    GlobalTapSettingsForm (TouchPad::TouchSettings &settings_);
    ~GlobalTapSettingsForm();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TouchPad::TouchSettings &settings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> label12;
    ScopedPointer<Label> label13;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label15;
    ScopedPointer<ComboBox> tap2Box;
    ScopedPointer<ComboBox> tap3Box;
    ScopedPointer<ComboBox> tap11Box;
    ScopedPointer<ComboBox> tap21Box;
    ScopedPointer<ComboBox> palmBox;
    ScopedPointer<ComboBox> swipeLeftBox;
    ScopedPointer<ComboBox> swipeRightBox;
    ScopedPointer<ComboBox> swipeUpBox;
    ScopedPointer<ComboBox> swipeDownBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalTapSettingsForm)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
