/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 800);


	// slider parameter
	midiVolume.setSliderStyle(Slider::LinearBarVertical); // slider style
	midiVolume.setRange(0.0, 127.0, 1.0);  // min max increment
	midiVolume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	midiVolume.setPopupDisplayEnabled(true, false, this); // show on drag, show on hover, parent
	midiVolume.setTextValueSuffix(" Volume"); // tooltip suffix
	midiVolume.setValue(100);

	// add slider to the editor
	addAndMakeVisible(&midiVolume);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // fill the background with a solid colour
    g.fillAll (Colours::beige);
	// set text color
    g.setColour (Colours::darkgreen);
	// set font size
    g.setFont (24.0f);
	// draw text
    g.drawFittedText ("Output Volume", 0,0, getWidth(), 30, Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	midiVolume.setBounds(40, 30, 20, getHeight() - 60);

}
