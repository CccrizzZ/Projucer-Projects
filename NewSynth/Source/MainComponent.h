/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    
    // Volume level
    float level = -18.0f;
    // Volume slider and label
    Slider VolumeSlider;
    Label volumeLabel;

    // random shit
    JUCE_API::Random random;

    Slider FrequencySlider;
    Label FrequencyLabel;

    double CurrentSampleRate = 0.0;
    double CurrentAngle = 0.0;
    double AngleDelta = 0.0;


    void updateAngleData();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
