/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_A86435CADD63662E__
#define __JUCE_HEADER_A86435CADD63662E__

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

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void loadSettings();
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<GroupComponent> scrollGrp;
    ScopedPointer<ComboBox> scrollModeBox;
    ScopedPointer<Slider> xSpeedSlider;
    ScopedPointer<Slider> ySpeedSlider;
    ScopedPointer<ComboBox> appCombo;
    ScopedPointer<ComboBox> xscrollMethod;
    ScopedPointer<Label> label4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ApplicationsettingsForm)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_A86435CADD63662E__
