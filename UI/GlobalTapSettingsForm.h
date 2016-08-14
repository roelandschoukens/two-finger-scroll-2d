/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  21 Apr 2012 2:02:07pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_GLOBALTAPSETTINGSFORM_GLOBALTAPSETTINGSFORM_7D94B33E__
#define __JUCER_HEADER_GLOBALTAPSETTINGSFORM_GLOBALTAPSETTINGSFORM_7D94B33E__

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

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	TouchPad::TouchSettings &settings;
    //[/UserVariables]

    //==============================================================================
    GroupComponent* groupComponent2;
    GroupComponent* groupComponent;
    Label* label6;
    Label* label8;
    Label* label9;
    Label* label10;
    Label* label11;
    Label* label12;
    Label* label13;
    Label* label14;
    Label* label15;
    ComboBox* tap2Box;
    ComboBox* tap3Box;
    ComboBox* tap11Box;
    ComboBox* tap21Box;
    ComboBox* palmBox;
    ComboBox* swipeLeftBox;
    ComboBox* swipeRightBox;
    ComboBox* swipeUpBox;
    ComboBox* swipeDownBox;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    GlobalTapSettingsForm (const GlobalTapSettingsForm&);
    const GlobalTapSettingsForm& operator= (const GlobalTapSettingsForm&);
};


#endif   // __JUCER_HEADER_GLOBALTAPSETTINGSFORM_GLOBALTAPSETTINGSFORM_7D94B33E__
