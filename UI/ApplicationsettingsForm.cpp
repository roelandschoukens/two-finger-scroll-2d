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

#include "ApplicationsettingsForm.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ApplicationsettingsForm::ApplicationsettingsForm (const String &appName)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("applicationsettings");
    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Mode")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("X speed")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Y speed")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (scrollGrp = new GroupComponent ("scroll group",
                                                       TRANS("Scrolling")));

    addAndMakeVisible (scrollModeBox = new ComboBox ("new combo box"));
    scrollModeBox->setEditableText (false);
    scrollModeBox->setJustificationType (Justification::centredLeft);
    scrollModeBox->setTextWhenNothingSelected (String());
    scrollModeBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    scrollModeBox->addItem (TRANS("Use global setting"), 1);
    scrollModeBox->addItem (TRANS("Discrete (old school)"), 2);
    scrollModeBox->addItem (TRANS("Continuous"), 3);
    scrollModeBox->addListener (this);

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

    addAndMakeVisible (appCombo = new ComboBox ("application"));
    appCombo->setEditableText (false);
    appCombo->setJustificationType (Justification::centredLeft);
    appCombo->setTextWhenNothingSelected (TRANS("(select an application)"));
    appCombo->setTextWhenNoChoicesAvailable (TRANS("(no applications)"));
    appCombo->addListener (this);

    addAndMakeVisible (xscrollMethod = new ComboBox ("x method"));
    xscrollMethod->setEditableText (false);
    xscrollMethod->setJustificationType (Justification::centredLeft);
    xscrollMethod->setTextWhenNothingSelected (String());
    xscrollMethod->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    xscrollMethod->addItem (TRANS("Standard"), 1);
    xscrollMethod->addItem (TRANS("Shift + scroll Y"), 2);
    xscrollMethod->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("X compatibility mode")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 208);


    //[Constructor] You can add your own custom stuff here..

	// list all applications with saved settings.
	StringArray apps = TouchPad::enumApplications();
	for (int i = 0; i < apps.size(); ++i)
	{
		appCombo->addItem(apps[i], i + 1);
		if (apps[i] == appName)
		{
			appCombo->setSelectedItemIndex(i);
		}
	}

	// If appName has no saved settings, make a blank one and add it to the list.
	if (appName.isNotEmpty() &&  appCombo->getSelectedId() == 0)
	{
		appCombo->addItem(appName, apps.size() + 1);
		appCombo->setSelectedItemIndex(apps.size());
	}

	loadSettings();
    //[/Constructor]
}

ApplicationsettingsForm::~ApplicationsettingsForm()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label5 = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    scrollGrp = nullptr;
    scrollModeBox = nullptr;
    xSpeedSlider = nullptr;
    ySpeedSlider = nullptr;
    appCombo = nullptr;
    xscrollMethod = nullptr;
    label4 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ApplicationsettingsForm::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ApplicationsettingsForm::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label5->setBounds (16, 64, 80, 23);
    label2->setBounds (16, 96, 88, 23);
    label3->setBounds (16, 128, 88, 23);
    scrollGrp->setBounds (8, 40, getWidth() - 16, getHeight() - 48);
    scrollModeBox->setBounds (136, 64, getWidth() - 164, 24);
    xSpeedSlider->setBounds (136, 96, getWidth() - 160, 24);
    ySpeedSlider->setBounds (136, 128, getWidth() - 160, 24);
    appCombo->setBounds (8, 8, getWidth() - 16, 24);
    xscrollMethod->setBounds (136, 160, getWidth() - 164, 24);
    label4->setBounds (16, 160, 120, 23);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ApplicationsettingsForm::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
	TouchPad::AppTouchSettings &settings = TouchPad::gEditSettings;
    //[/UsercomboBoxChanged_Pre]

	if (comboBoxThatHasChanged == scrollModeBox)
	{
		//[UserComboBoxCode_scrollModeBox] -- add your combo box handling code here..
		TouchPad::ScrollMode modes[] = {
			TouchPad::S_Inherit,
			TouchPad::S_Discrete,
			TouchPad::S_Smooth
		};
		int ch = jlimit(1, 3, scrollModeBox->getSelectedId());
		settings.scrollMode = modes[ch - 1];
		//[/UserComboBoxCode_scrollModeBox]
    }
    else if (comboBoxThatHasChanged == appCombo)
    {
        //[UserComboBoxCode_appCombo] -- add your combo box handling code here..
		TouchPad::saveAppSettings(TouchPad::gEditAppName, settings);
		loadSettings();
        //[/UserComboBoxCode_appCombo]
    }
    else if (comboBoxThatHasChanged == xscrollMethod)
    {
        //[UserComboBoxCode_xscrollMethod] -- add your combo box handling code here..
		TouchPad::XScrollMode modes[] = {
			TouchPad::S_X_Standard,
			TouchPad::S_X_ShiftY
		};
		int ch = jlimit(1, 2, scrollModeBox->getSelectedId());
		settings.xScrollMode = modes[ch - 1];
		//[/UserComboBoxCode_xscrollMethod]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ApplicationsettingsForm::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	TouchPad::AppTouchSettings &settings = TouchPad::gEditSettings;
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ApplicationsettingsForm::loadSettings()
{
	bool enabled = (appCombo->getSelectedId() != 0);
	if (enabled)
	{
		TouchPad::AppTouchSettings &settings = TouchPad::gEditSettings;
		TouchPad::loadAppSettings(appCombo->getText(), settings);
		TouchPad::gEditAppName = appCombo->getText();

		switch (settings.scrollMode)
		{
		case TouchPad::S_Inherit: scrollModeBox->setSelectedId(1, dontSendNotification); break;
		case TouchPad::S_Discrete: scrollModeBox->setSelectedId(2, dontSendNotification); break;
		case TouchPad::S_Smooth: scrollModeBox->setSelectedId(3, dontSendNotification); break;
		}
		switch (settings.xScrollMode)
		{
		case TouchPad::S_X_Standard: xscrollMethod->setSelectedId(1, dontSendNotification); break;
		case TouchPad::S_X_ShiftY: xscrollMethod->setSelectedId(2, dontSendNotification); break;
		}
		xSpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_X]);
		ySpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_Y]);
	}
	else
	{
		TouchPad::gEditAppName = "";
	}
	scrollModeBox->setEnabled(enabled);
	xscrollMethod->setEnabled(enabled);
	xSpeedSlider->setEnabled(enabled);
	ySpeedSlider->setEnabled(enabled);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ApplicationsettingsForm"
                 componentName="applicationsettings" parentClasses="public Component"
                 constructorParams="const String &amp;appName" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="208">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="f25b8dd62abd2f29" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="16 64 80 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="23af637525ce5249" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 96 88 23" edTextCol="ff000000"
         edBkgCol="0" labelText="X speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2892c2b1cf67ec1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 128 88 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Y speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="scroll group" id="71a5842afcf439c5" memberName="scrollGrp"
                  virtualName="" explicitFocusOrder="0" pos="8 40 16M 48M" title="Scrolling"/>
  <COMBOBOX name="new combo box" id="82c87582d5d5220a" memberName="scrollModeBox"
            virtualName="" explicitFocusOrder="0" pos="136 64 164M 24" editable="0"
            layout="33" items="Use global setting&#10;Discrete (old school)&#10;Continuous"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2129cdec476a3b84" memberName="xSpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="136 96 160M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="new slider" id="7b6701a5fe87ca59" memberName="ySpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="136 128 160M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <COMBOBOX name="application" id="30387f33922a6b6e" memberName="appCombo"
            virtualName="" explicitFocusOrder="0" pos="8 8 16M 24" editable="0"
            layout="33" items="" textWhenNonSelected="(select an application)"
            textWhenNoItems="(no applications)"/>
  <COMBOBOX name="x method" id="f0bc5939d5c84bac" memberName="xscrollMethod"
            virtualName="" explicitFocusOrder="0" pos="136 160 164M 24" editable="0"
            layout="33" items="Standard&#10;Shift + scroll Y" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="a8257059a652b48c" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 160 120 23" edTextCol="ff000000"
         edBkgCol="0" labelText="X compatibility mode" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
