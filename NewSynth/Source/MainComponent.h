/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineWaveSound.h"
#include "SynthAudioSource.h"
#include "SineWaveVoice.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public AudioAppComponent, private Timer
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
    

    void timerCallback()override
    {
        Keyboard1.grabKeyboardFocus();
        stopTimer();
    }

    
    // Volume level
    float level = -18.0f;


    // random shit
    JUCE_API::Random random;
    
    // Volume slider and label
    Slider VolumeSlider;
    Label volumeLabel;

    // Frequency slider and label
    Slider FrequencySlider;
    Label FrequencyLabel;


    // Sine wave shit
    double CurrentSampleRate = 0.0;
    double CurrentAngle = 0.0;
    double AngleDelta = 0.0;
    void updateAngleData();
    
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent Keyboard1;
    SynthAudioSource sAudioSource;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
