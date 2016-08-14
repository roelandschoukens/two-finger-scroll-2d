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

//[Headers] You can add your own extra header files here...
#include "TouchSettings.h"
//[/Headers]

#include "GlobalScrollSettingsForm.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GlobalScrollSettingsForm::GlobalScrollSettingsForm (TouchPad::TouchSettings &settings_)
    : settings(settings_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (scrollGrp2 = new GroupComponent ("scroll group",
                                                        TRANS("Options")));

    addAndMakeVisible (scrollGrp = new GroupComponent ("scroll group",
                                                       TRANS("Speed")));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("X speed")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Y speed")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Momentum")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Mode")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("X snap")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Y snap")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (xSpeedSlider = new Slider ("new slider"));
    xSpeedSlider->setRange (0, 100, 0);
    xSpeedSlider->setSliderStyle (Slider::LinearHorizontal);
    xSpeedSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    xSpeedSlider->addListener (this);

    addAndMakeVisible (ySpeedSlider = new Slider ("new slider"));
    ySpeedSlider->setRange (0, 100, 0);
    ySpeedSlider->setSliderStyle (Slider::LinearHorizontal);
    ySpeedSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    ySpeedSlider->addListener (this);

    addAndMakeVisible (xSnapSlider = new Slider ("new slider"));
    xSnapSlider->setRange (0, 120, 0);
    xSnapSlider->setSliderStyle (Slider::LinearHorizontal);
    xSnapSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    xSnapSlider->addListener (this);

    addAndMakeVisible (ySnapSlider = new Slider ("new slider"));
    ySnapSlider->setRange (0, 120, 0);
    ySnapSlider->setSliderStyle (Slider::LinearHorizontal);
    ySnapSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    ySnapSlider->addListener (this);

    addAndMakeVisible (scrollModeBox = new ComboBox ("new combo box"));
    scrollModeBox->setEditableText (false);
    scrollModeBox->setJustificationType (Justification::centredLeft);
    scrollModeBox->setTextWhenNothingSelected (String());
    scrollModeBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    scrollModeBox->addItem (TRANS("Discrete (old school)"), 1);
    scrollModeBox->addItem (TRANS("Continuous"), 2);
    scrollModeBox->addListener (this);

    addAndMakeVisible (momentumSlider = new Slider ("new slider"));
    momentumSlider->setRange (0, 100, 1);
    momentumSlider->setSliderStyle (Slider::LinearHorizontal);
    momentumSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    momentumSlider->addListener (this);
    momentumSlider->setSkewFactor (4);

    addAndMakeVisible (intuitiveBtn = new ToggleButton ("new toggle button"));
    intuitiveBtn->setButtonText (TRANS("Intuitive scrolling"));
    intuitiveBtn->addListener (this);

    addAndMakeVisible (accelerationBtn = new ToggleButton ("new toggle button"));
    accelerationBtn->setButtonText (TRANS("Acceleration"));
    accelerationBtn->addListener (this);

    addAndMakeVisible (accelerationSlider = new Slider ("acceleration"));
    accelerationSlider->setRange (0, 90, 1);
    accelerationSlider->setSliderStyle (Slider::LinearHorizontal);
    accelerationSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    accelerationSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 328);


    //[Constructor] You can add your own custom stuff here..
	xSpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_X]);
	ySpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_Y]);
	accelerationBtn->setToggleState(settings.scrollAcc != 0, dontSendNotification);
	accelerationSlider->setValue(settings.scrollAcc != 0 ? (120 - settings.scrollAcc) : 75);
	momentumSlider->setValue(settings.scrollMomentum);
	xSnapSlider->setValue(settings.scrollSnap[TouchPad::AXIS_X]);
	ySnapSlider->setValue(settings.scrollSnap[TouchPad::AXIS_Y]);
	scrollModeBox->setSelectedId(settings.scrollMode == TouchPad::S_Discrete ? 1 : 2, dontSendNotification);
	intuitiveBtn->setToggleState(settings.scrollIntuitive, dontSendNotification);
    //[/Constructor]
}

GlobalScrollSettingsForm::~GlobalScrollSettingsForm()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    scrollGrp2 = nullptr;
    scrollGrp = nullptr;
    label = nullptr;
    label2 = nullptr;
    label7 = nullptr;
    label5 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    xSpeedSlider = nullptr;
    ySpeedSlider = nullptr;
    xSnapSlider = nullptr;
    ySnapSlider = nullptr;
    scrollModeBox = nullptr;
    momentumSlider = nullptr;
    intuitiveBtn = nullptr;
    accelerationBtn = nullptr;
    accelerationSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GlobalScrollSettingsForm::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GlobalScrollSettingsForm::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    scrollGrp2->setBounds (8, 168, getWidth() - 16, 152);
    scrollGrp->setBounds (8, 8, getWidth() - 16, 152);
    label->setBounds (16, 32, 80, 24);
    label2->setBounds (16, 64, 80, 24);
    label7->setBounds (16, 128, 80, 24);
    label5->setBounds (16, 192, 80, 24);
    label3->setBounds (16, 224, 80, 24);
    label4->setBounds (16, 256, 80, 24);
    xSpeedSlider->setBounds (96, 32, getWidth() - 120, 24);
    ySpeedSlider->setBounds (96, 64, getWidth() - 120, 24);
    xSnapSlider->setBounds (96, 224, getWidth() - 120, 24);
    ySnapSlider->setBounds (96, 256, getWidth() - 120, 24);
    scrollModeBox->setBounds (96, 192, getWidth() - 120, 24);
    momentumSlider->setBounds (96, 128, getWidth() - 120, 24);
    intuitiveBtn->setBounds (16, 288, 264, 24);
    accelerationBtn->setBounds (16, 96, 104, 24);
    accelerationSlider->setBounds (120, 96, getWidth() - 144, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GlobalScrollSettingsForm::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == xSpeedSlider)
    {
        //[UserSliderCode_xSpeedSlider] -- add your slider handling code here..
		settings.scrollSpeed[TouchPad::AXIS_X] = (int) xSpeedSlider->getValue();
        //[/UserSliderCode_xSpeedSlider]
    }
    else if (sliderThatWasMoved == ySpeedSlider)
    {
        //[UserSliderCode_ySpeedSlider] -- add your slider handling code here..
		settings.scrollSpeed[TouchPad::AXIS_Y] = (int) ySpeedSlider->getValue();
        //[/UserSliderCode_ySpeedSlider]
    }
    else if (sliderThatWasMoved == xSnapSlider)
    {
        //[UserSliderCode_xSnapSlider] -- add your slider handling code here..
		settings.scrollSnap[TouchPad::AXIS_X] = (int) xSnapSlider->getValue();
        //[/UserSliderCode_xSnapSlider]
    }
    else if (sliderThatWasMoved == ySnapSlider)
    {
        //[UserSliderCode_ySnapSlider] -- add your slider handling code here..
		settings.scrollSnap[TouchPad::AXIS_Y] = (int) ySnapSlider->getValue();
        //[/UserSliderCode_ySnapSlider]
    }
    else if (sliderThatWasMoved == momentumSlider)
    {
        //[UserSliderCode_momentumSlider] -- add your slider handling code here..
		settings.scrollMomentum = (int) momentumSlider->getValue();
        //[/UserSliderCode_momentumSlider]
    }
    else if (sliderThatWasMoved == accelerationSlider)
    {
        //[UserSliderCode_accelerationSlider] -- add your slider handling code here..
		settings.scrollAcc = 120 - (int) accelerationSlider->getValue();
        //[/UserSliderCode_accelerationSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GlobalScrollSettingsForm::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == scrollModeBox)
    {
        //[UserComboBoxCode_scrollModeBox] -- add your combo box handling code here..
		settings.scrollMode = scrollModeBox->getSelectedId() == 1 ? TouchPad::S_Discrete : TouchPad::S_Smooth;
        //[/UserComboBoxCode_scrollModeBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void GlobalScrollSettingsForm::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == intuitiveBtn)
    {
        //[UserButtonCode_intuitiveBtn] -- add your button handler code here..
		settings.scrollIntuitive = intuitiveBtn->getToggleState();
        //[/UserButtonCode_intuitiveBtn]
    }
    else if (buttonThatWasClicked == accelerationBtn)
    {
        //[UserButtonCode_accelerationBtn] -- add your button handler code here..
		accelerationSlider->setEnabled(accelerationBtn->getToggleState());
		settings.scrollAcc = accelerationBtn->getToggleState() ? 120 - (int) accelerationSlider->getValue() : 0;
        //[/UserButtonCode_accelerationBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GlobalScrollSettingsForm"
                 componentName="" parentClasses="public Component" constructorParams="TouchPad::TouchSettings &amp;settings_"
                 variableInitialisers="settings(settings_)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="400"
                 initialHeight="328">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="scroll group" id="bf2ba31e96207190" memberName="scrollGrp2"
                  virtualName="" explicitFocusOrder="0" pos="8 168 16M 152" title="Options"/>
  <GROUPCOMPONENT name="scroll group" id="71a5842afcf439c5" memberName="scrollGrp"
                  virtualName="" explicitFocusOrder="0" pos="8 8 16M 152" title="Speed"/>
  <LABEL name="new label" id="5dc5262c212f57f" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 32 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="X speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="759f5be774bc0c2f" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 64 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Y speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="79e9b7d8b3f79199" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16 128 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Momentum" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f25b8dd62abd2f29" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="16 192 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c10533febcce0c43" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 224 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="X snap" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e1687949cbbfd89e" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 256 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Y snap" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="211875d6c0a2b7f9" memberName="xSpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="96 32 120M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="2129cdec476a3b84" memberName="ySpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="96 64 120M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="30b41154a306e11" memberName="xSnapSlider"
          virtualName="" explicitFocusOrder="0" pos="96 224 120M 24" min="0"
          max="120" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="ca770bc518aa6804" memberName="ySnapSlider"
          virtualName="" explicitFocusOrder="0" pos="96 256 120M 24" min="0"
          max="120" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="new combo box" id="82c87582d5d5220a" memberName="scrollModeBox"
            virtualName="" explicitFocusOrder="0" pos="96 192 120M 24" editable="0"
            layout="33" items="Discrete (old school)&#10;Continuous" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="cc55fbe0cf08a42b" memberName="momentumSlider"
          virtualName="" explicitFocusOrder="0" pos="96 128 120M 24" min="0"
          max="100" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="4"
          needsCallback="1"/>
  <TOGGLEBUTTON name="new toggle button" id="60dcb4b24f0ea202" memberName="intuitiveBtn"
                virtualName="" explicitFocusOrder="0" pos="16 288 264 24" buttonText="Intuitive scrolling"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="b53d0e3bc47b8936" memberName="accelerationBtn"
                virtualName="" explicitFocusOrder="0" pos="16 96 104 24" buttonText="Acceleration"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="acceleration" id="971237400b1306a2" memberName="accelerationSlider"
          virtualName="" explicitFocusOrder="0" pos="120 96 144M 24" min="0"
          max="90" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
