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

//[Headers] You can add your own extra header files here...
#include "TouchSettings.h"
//[/Headers]

#include "GlobalTapSettingsForm.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
void fillTapBox(ComboBox *box, TouchPad::ActionId selected)
{
	for (unsigned int i = 0; i < TouchPad::TA_TAEnd; ++i)
	{
		box->addItem(String(TouchPad::tapNames[i]), 1 + i);
	}
	box->setSelectedId(selected + 1, true);
}
//[/MiscUserDefs]

//==============================================================================
GlobalTapSettingsForm::GlobalTapSettingsForm (TouchPad::TouchSettings &settings_)
    : settings(settings_),
      groupComponent2 (0),
      groupComponent (0),
      label6 (0),
      label8 (0),
      label9 (0),
      label10 (0),
      label11 (0),
      label12 (0),
      label13 (0),
      label14 (0),
      label15 (0),
      tap2Box (0),
      tap3Box (0),
      tap11Box (0),
      tap21Box (0),
      palmBox (0),
      swipeLeftBox (0),
      swipeRightBox (0),
      swipeUpBox (0),
      swipeDownBox (0)
{
    addAndMakeVisible (groupComponent2 = new GroupComponent (L"new group",
                                                             L"3 finger swipe"));

    addAndMakeVisible (groupComponent = new GroupComponent (L"new group",
                                                            L"Tap actions"));

    addAndMakeVisible (label6 = new Label (L"new label",
                                           L"2 fingers"));
    label6->setFont (Font (15.0000f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label8 = new Label (L"new label",
                                           L"3 fingers"));
    label8->setFont (Font (15.0000f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label9 = new Label (L"new label",
                                           L"1+1"));
    label9->setFont (Font (15.0000f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label10 = new Label (L"new label",
                                            L"2+1"));
    label10->setFont (Font (15.0000f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label11 = new Label (L"new label",
                                            L"Palm"));
    label11->setFont (Font (15.0000f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label12 = new Label (L"new label",
                                            L"Left"));
    label12->setFont (Font (15.0000f, Font::plain));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label13 = new Label (L"new label",
                                            L"Right"));
    label13->setFont (Font (15.0000f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label14 = new Label (L"new label",
                                            L"Up"));
    label14->setFont (Font (15.0000f, Font::plain));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label15 = new Label (L"new label",
                                            L"Down"));
    label15->setFont (Font (15.0000f, Font::plain));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (tap2Box = new ComboBox (L"new combo box"));
    tap2Box->setEditableText (false);
    tap2Box->setJustificationType (Justification::centredLeft);
    tap2Box->setTextWhenNothingSelected (String::empty);
    tap2Box->setTextWhenNoChoicesAvailable (L"(no choices)");
    tap2Box->addListener (this);

    addAndMakeVisible (tap3Box = new ComboBox (L"new combo box"));
    tap3Box->setEditableText (false);
    tap3Box->setJustificationType (Justification::centredLeft);
    tap3Box->setTextWhenNothingSelected (String::empty);
    tap3Box->setTextWhenNoChoicesAvailable (L"(no choices)");
    tap3Box->addListener (this);

    addAndMakeVisible (tap11Box = new ComboBox (L"new combo box"));
    tap11Box->setEditableText (false);
    tap11Box->setJustificationType (Justification::centredLeft);
    tap11Box->setTextWhenNothingSelected (String::empty);
    tap11Box->setTextWhenNoChoicesAvailable (L"(no choices)");
    tap11Box->addListener (this);

    addAndMakeVisible (tap21Box = new ComboBox (L"new combo box"));
    tap21Box->setEditableText (false);
    tap21Box->setJustificationType (Justification::centredLeft);
    tap21Box->setTextWhenNothingSelected (String::empty);
    tap21Box->setTextWhenNoChoicesAvailable (L"(no choices)");
    tap21Box->addListener (this);

    addAndMakeVisible (palmBox = new ComboBox (L"new combo box"));
    palmBox->setEditableText (false);
    palmBox->setJustificationType (Justification::centredLeft);
    palmBox->setTextWhenNothingSelected (String::empty);
    palmBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    palmBox->addListener (this);

    addAndMakeVisible (swipeLeftBox = new ComboBox (L"new combo box"));
    swipeLeftBox->setEditableText (false);
    swipeLeftBox->setJustificationType (Justification::centredLeft);
    swipeLeftBox->setTextWhenNothingSelected (String::empty);
    swipeLeftBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    swipeLeftBox->addListener (this);

    addAndMakeVisible (swipeRightBox = new ComboBox (L"new combo box"));
    swipeRightBox->setEditableText (false);
    swipeRightBox->setJustificationType (Justification::centredLeft);
    swipeRightBox->setTextWhenNothingSelected (String::empty);
    swipeRightBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    swipeRightBox->addListener (this);

    addAndMakeVisible (swipeUpBox = new ComboBox (L"new combo box"));
    swipeUpBox->setEditableText (false);
    swipeUpBox->setJustificationType (Justification::centredLeft);
    swipeUpBox->setTextWhenNothingSelected (String::empty);
    swipeUpBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    swipeUpBox->addListener (this);

    addAndMakeVisible (swipeDownBox = new ComboBox (L"new combo box"));
    swipeDownBox->setEditableText (false);
    swipeDownBox->setJustificationType (Justification::centredLeft);
    swipeDownBox->setTextWhenNothingSelected (String::empty);
    swipeDownBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    swipeDownBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (304, 360);


    //[Constructor] You can add your own custom stuff here..
	fillTapBox(tap2Box, settings.tapTwo);
	fillTapBox(tap3Box, settings.tapThree);
	fillTapBox(tap11Box, settings.tapOneOne);
	fillTapBox(tap21Box, settings.tapTwoOne);
	fillTapBox(palmBox, settings.palm);
	fillTapBox(swipeLeftBox, settings.swipe3[TouchPad::D_Left]);
	fillTapBox(swipeRightBox, settings.swipe3[TouchPad::D_Right]);
	fillTapBox(swipeUpBox, settings.swipe3[TouchPad::D_Up]);
	fillTapBox(swipeDownBox, settings.swipe3[TouchPad::D_Down]);
    //[/Constructor]
}

GlobalTapSettingsForm::~GlobalTapSettingsForm()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (groupComponent2);
    deleteAndZero (groupComponent);
    deleteAndZero (label6);
    deleteAndZero (label8);
    deleteAndZero (label9);
    deleteAndZero (label10);
    deleteAndZero (label11);
    deleteAndZero (label12);
    deleteAndZero (label13);
    deleteAndZero (label14);
    deleteAndZero (label15);
    deleteAndZero (tap2Box);
    deleteAndZero (tap3Box);
    deleteAndZero (tap11Box);
    deleteAndZero (tap21Box);
    deleteAndZero (palmBox);
    deleteAndZero (swipeLeftBox);
    deleteAndZero (swipeRightBox);
    deleteAndZero (swipeUpBox);
    deleteAndZero (swipeDownBox);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GlobalTapSettingsForm::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GlobalTapSettingsForm::resized()
{
    groupComponent2->setBounds (8, 200, getWidth() - 16, 152);
    groupComponent->setBounds (8, 8, getWidth() - 16, 184);
    label6->setBounds (16, 32, 80, 23);
    label8->setBounds (16, 64, 80, 23);
    label9->setBounds (16, 96, 80, 23);
    label10->setBounds (16, 128, 80, 23);
    label11->setBounds (16, 160, 80, 23);
    label12->setBounds (16, 224, 80, 23);
    label13->setBounds (16, 256, 80, 23);
    label14->setBounds (16, 288, 80, 23);
    label15->setBounds (16, 320, 80, 23);
    tap2Box->setBounds (96, 32, getWidth() - 128, 24);
    tap3Box->setBounds (96, 64, getWidth() - 128, 24);
    tap11Box->setBounds (96, 96, getWidth() - 128, 24);
    tap21Box->setBounds (96, 128, getWidth() - 128, 24);
    palmBox->setBounds (96, 160, getWidth() - 128, 24);
    swipeLeftBox->setBounds (96, 224, getWidth() - 128, 24);
    swipeRightBox->setBounds (96, 256, getWidth() - 128, 24);
    swipeUpBox->setBounds (96, 288, getWidth() - 128, 24);
    swipeDownBox->setBounds (96, 320, getWidth() - 128, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GlobalTapSettingsForm::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == tap2Box)
    {
        //[UserComboBoxCode_tap2Box] -- add your combo box handling code here..
		settings.tapTwo = tap2Box->getSelectedId() - 1;
        //[/UserComboBoxCode_tap2Box]
    }
    else if (comboBoxThatHasChanged == tap3Box)
    {
        //[UserComboBoxCode_tap3Box] -- add your combo box handling code here..
		settings.tapThree = tap3Box->getSelectedId() - 1;
        //[/UserComboBoxCode_tap3Box]
    }
    else if (comboBoxThatHasChanged == tap11Box)
    {
        //[UserComboBoxCode_tap11Box] -- add your combo box handling code here..
		settings.tapOneOne= tap11Box->getSelectedId() - 1;
        //[/UserComboBoxCode_tap11Box]
    }
    else if (comboBoxThatHasChanged == tap21Box)
    {
        //[UserComboBoxCode_tap21Box] -- add your combo box handling code here..
		settings.tapTwoOne = tap21Box->getSelectedId() - 1;
        //[/UserComboBoxCode_tap21Box]
    }
    else if (comboBoxThatHasChanged == palmBox)
    {
        //[UserComboBoxCode_palmBox] -- add your combo box handling code here..
		settings.palm = palmBox->getSelectedId() - 1;
        //[/UserComboBoxCode_palmBox]
    }
    else if (comboBoxThatHasChanged == swipeLeftBox)
    {
        //[UserComboBoxCode_swipeLeftBox] -- add your combo box handling code here..
		settings.swipe3[TouchPad::D_Left] = swipeLeftBox->getSelectedId() - 1;
        //[/UserComboBoxCode_swipeLeftBox]
    }
    else if (comboBoxThatHasChanged == swipeRightBox)
    {
        //[UserComboBoxCode_swipeRightBox] -- add your combo box handling code here..
		settings.swipe3[TouchPad::D_Right] = swipeRightBox->getSelectedId() - 1;
        //[/UserComboBoxCode_swipeRightBox]
    }
    else if (comboBoxThatHasChanged == swipeUpBox)
    {
        //[UserComboBoxCode_swipeUpBox] -- add your combo box handling code here..
		settings.swipe3[TouchPad::D_Up] = swipeUpBox->getSelectedId() - 1;
        //[/UserComboBoxCode_swipeUpBox]
    }
    else if (comboBoxThatHasChanged == swipeDownBox)
    {
        //[UserComboBoxCode_swipeDownBox] -- add your combo box handling code here..
		settings.swipe3[TouchPad::D_Down] = swipeDownBox->getSelectedId() - 1;
        //[/UserComboBoxCode_swipeDownBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GlobalTapSettingsForm" componentName=""
                 parentClasses="public Component" constructorParams="TouchPad::TouchSettings &amp;settings_"
                 variableInitialisers="settings(settings_)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="304"
                 initialHeight="360">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="99dbf559319688ef" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="8 200 16M 152" title="3 finger swipe"/>
  <GROUPCOMPONENT name="new group" id="e378add1176af53b" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 8 16M 184" title="Tap actions"/>
  <LABEL name="new label" id="d2a14e9deb2164ff" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="16 32 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="2 fingers" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="716855a3dfa3c50d" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="16 64 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="3 fingers" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bf5f9891cff989ff" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="16 96 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="1+1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="156d8ad1a6e2b252" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="16 128 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="2+1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bde24b501cac24df" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="16 160 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Palm" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fcf73b4c0a508cb" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="16 224 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Left" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fb4bc10289a6b16a" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="16 256 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Right" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="799c1a5a60610e12" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="16 288 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Up" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="80e4033d51e737d4" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="16 320 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Down" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="df01c9ad58b72271" memberName="tap2Box"
            virtualName="" explicitFocusOrder="0" pos="96 32 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="6a5ca09463c22de2" memberName="tap3Box"
            virtualName="" explicitFocusOrder="0" pos="96 64 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="405e36ca45326ec3" memberName="tap11Box"
            virtualName="" explicitFocusOrder="0" pos="96 96 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="5c8a2204d0da333e" memberName="tap21Box"
            virtualName="" explicitFocusOrder="0" pos="96 128 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="4c48a007ace8bef5" memberName="palmBox"
            virtualName="" explicitFocusOrder="0" pos="96 160 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="208f906957caf04d" memberName="swipeLeftBox"
            virtualName="" explicitFocusOrder="0" pos="96 224 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="3db6af727c5ff258" memberName="swipeRightBox"
            virtualName="" explicitFocusOrder="0" pos="96 256 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="4cce00219b043da9" memberName="swipeUpBox"
            virtualName="" explicitFocusOrder="0" pos="96 288 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="6402c943a70ed8b0" memberName="swipeDownBox"
            virtualName="" explicitFocusOrder="0" pos="96 320 128M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
