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

//[Headers] You can add your own extra header files here...
#include "TouchSettings.h"
//[/Headers]

#include "ApplicationsettingsForm.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ApplicationsettingsForm::ApplicationsettingsForm (const String &appName)
    : Component ("applicationsettings"),
      scrollGrp (0),
      label5 (0),
      scrollModeBox (0),
      xSpeedSlider (0),
      label2 (0),
      ySpeedSlider (0),
      label3 (0),
      appCombo (0)
{
    addAndMakeVisible (scrollGrp = new GroupComponent ("scroll group",
                                                       "Scrolling"));

    addAndMakeVisible (label5 = new Label ("new label",
                                           "Mode"));
    label5->setFont (Font (15.0000f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (scrollModeBox = new ComboBox ("new combo box"));
    scrollModeBox->setEditableText (false);
    scrollModeBox->setJustificationType (Justification::centredLeft);
    scrollModeBox->setTextWhenNothingSelected (String::empty);
    scrollModeBox->setTextWhenNoChoicesAvailable ("(no choices)");
    scrollModeBox->addItem ("Use global setting", 1);
    scrollModeBox->addItem ("Discrete (old school)", 2);
    scrollModeBox->addItem ("Continuous", 3);
    scrollModeBox->addListener (this);

    addAndMakeVisible (xSpeedSlider = new Slider ("new slider"));
    xSpeedSlider->setRange (0, 100, 0);
    xSpeedSlider->setSliderStyle (Slider::LinearHorizontal);
    xSpeedSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    xSpeedSlider->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           "X speed"));
    label2->setFont (Font (15.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (ySpeedSlider = new Slider ("new slider"));
    ySpeedSlider->setRange (0, 100, 0);
    ySpeedSlider->setSliderStyle (Slider::LinearHorizontal);
    ySpeedSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    ySpeedSlider->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           "Y speed"));
    label3->setFont (Font (15.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (appCombo = new ComboBox ("application"));
    appCombo->setEditableText (false);
    appCombo->setJustificationType (Justification::centredLeft);
    appCombo->setTextWhenNothingSelected ("(select an application)");
    appCombo->setTextWhenNoChoicesAvailable ("(no applications)");
    appCombo->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 168);


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

    deleteAndZero (scrollGrp);
    deleteAndZero (label5);
    deleteAndZero (scrollModeBox);
    deleteAndZero (xSpeedSlider);
    deleteAndZero (label2);
    deleteAndZero (ySpeedSlider);
    deleteAndZero (label3);
    deleteAndZero (appCombo);


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
    scrollGrp->setBounds (8, 40, getWidth() - 16, getHeight() - 48);
    label5->setBounds (16, 64, 88, 23);
    scrollModeBox->setBounds (96, 64, getWidth() - 124, 24);
    xSpeedSlider->setBounds (96, 96, getWidth() - 120, 24);
    label2->setBounds (16, 96, 88, 23);
    ySpeedSlider->setBounds (96, 128, getWidth() - 120, 24);
    label3->setBounds (16, 128, 88, 23);
    appCombo->setBounds (8, 8, getWidth() - 16, 24);
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
		if (scrollModeBox->getSelectedId() == 1)
		{
			settings.scrollMode = TouchPad::S_Inherit;
		}
		else
		{
			settings.scrollMode = scrollModeBox->getSelectedId() == 2 ? TouchPad::S_Discrete : TouchPad::S_Smooth;
		}
        //[/UserComboBoxCode_scrollModeBox]
    }
    else if (comboBoxThatHasChanged == appCombo)
    {
        //[UserComboBoxCode_appCombo] -- add your combo box handling code here..
		TouchPad::saveAppSettings(TouchPad::gEditAppName, settings);
		loadSettings();
        //[/UserComboBoxCode_appCombo]
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

		if (settings.scrollMode == TouchPad::S_Inherit)
		{
			scrollModeBox->setSelectedId(1, true);
		}
		else
		{
			scrollModeBox->setSelectedId(settings.scrollMode == TouchPad::S_Discrete ? 2 : 3, true);
		}
		xSpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_X]);
		ySpeedSlider->setValue(settings.scrollSpeed[TouchPad::AXIS_Y]);
	}
	else
	{
		TouchPad::gEditAppName = "";
	}
	scrollModeBox->setEnabled(enabled);
	xSpeedSlider->setEnabled(enabled);
	ySpeedSlider->setEnabled(enabled);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ApplicationsettingsForm"
                 componentName="applicationsettings" parentClasses="public Component"
                 constructorParams="const String &amp;appName" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="300" initialHeight="168">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="scroll group" id="71a5842afcf439c5" memberName="scrollGrp"
                  virtualName="" explicitFocusOrder="0" pos="8 40 16M 48M" title="Scrolling"/>
  <LABEL name="new label" id="f25b8dd62abd2f29" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="16 64 88 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Mode" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="82c87582d5d5220a" memberName="scrollModeBox"
            virtualName="" explicitFocusOrder="0" pos="96 64 124M 24" editable="0"
            layout="33" items="Use global setting&#10;Discrete (old school)&#10;Continuous"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="new slider" id="2129cdec476a3b84" memberName="xSpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="96 96 120M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="23af637525ce5249" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 96 88 23" edTextCol="ff000000"
         edBkgCol="0" labelText="X speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="7b6701a5fe87ca59" memberName="ySpeedSlider"
          virtualName="" explicitFocusOrder="0" pos="96 128 120M 24" min="0"
          max="100" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2892c2b1cf67ec1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 128 88 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Y speed" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="application" id="30387f33922a6b6e" memberName="appCombo"
            virtualName="" explicitFocusOrder="0" pos="8 8 16M 24" editable="0"
            layout="33" items="" textWhenNonSelected="(select an application)"
            textWhenNoItems="(no applications)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
