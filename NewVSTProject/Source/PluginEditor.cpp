/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewVstprojectAudioProcessorEditor::NewVstprojectAudioProcessorEditor (NewVstprojectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    

    // slider for gain
    gainSlider.setSliderStyle(Slider::LinearBar);
    gainSlider.setRange(juce::Range<double>(0.0, 1.0), 0.1);
    gainSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 90, 0);
    gainSlider.setPopupDisplayEnabled(false, false, this);
    //gainSlider.setTextValueSuffix("Gain ");
    gainSlider.setValue(0.5);
    gainSlider.setColour(Slider::ColourIds::textBoxTextColourId, Colours::white);
    gainSlider.setColour(Slider::ColourIds::trackColourId, Colours::limegreen);

    
    gainSlider.addListener(this);
    addAndMakeVisible(&gainSlider);



    // lable for gain
    gainLable.setText("Gain", dontSendNotification);
    gainLable.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLable);



}




NewVstprojectAudioProcessorEditor::~NewVstprojectAudioProcessorEditor()
{
}

//==============================================================================
void NewVstprojectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour (Colours::white);
    g.setFont (15.0f);

    gainAMT = gainSlider.getValue();
    g.drawFittedText((String)(gainAMT), 10, 40, getWidth(), 30, Justification::left, 1);


}

void NewVstprojectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // posX, posY, Width, Height
    gainSlider.setBounds(100, 35, 200, 20);
}

void NewVstprojectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider)
    {
        *(processor.gain) = gainSlider.getValue();
        gainAMT = 0;

    }

}
