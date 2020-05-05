/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 300);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    VolumeSlider.setSliderStyle(Slider::LinearBar);
    VolumeSlider.setRange(Range<double>(0.0, 1.0), 0.01);
    VolumeSlider.setColour(Slider::ColourIds::trackColourId, Colours::limegreen);
    VolumeSlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::limegreen);

    addAndMakeVisible(VolumeSlider);


    volumeLabel.setText("Volume: ", dontSendNotification);
    volumeLabel.attachToComponent(&VolumeSlider, true);
    addAndMakeVisible(volumeLabel);


    FrequencySlider.setSliderStyle(Slider::LinearBar);
    FrequencySlider.setRange(Range<double>(50.0, 5000.0), 1.0);
    FrequencySlider.setSkewFactorFromMidPoint(500.0);
    FrequencySlider.setTextValueSuffix("Hz");
    FrequencySlider.setColour(Slider::ColourIds::trackColourId, Colours::limegreen);
    FrequencySlider.setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::limegreen);
    addAndMakeVisible(FrequencySlider);


    FrequencyLabel.setText("Frequency: ", dontSendNotification);
    FrequencyLabel.attachToComponent(&FrequencySlider, true);
    addAndMakeVisible(FrequencyLabel);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()


    String message;
    message << "Preparing to play audio..." << newLine;
    message << " samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
    message << " sampleRate = " << sampleRate;
    Logger::getCurrentLogger()->writeToLog(message);




    CurrentSampleRate = sampleRate;
    updateAngleData();



}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    //bufferToFill.clearActiveBufferRegion();

    auto level = (float)VolumeSlider.getValue();
    auto LevelScale = level * 2.0f;

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            buffer[sample] = random.nextFloat() * LevelScale - level;
        }
    }

    auto FreqLevel = (float)FrequencySlider.getValue();
    auto* LeftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* RightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        auto CurrentSample = (float)std::sin(CurrentAngle);
        CurrentAngle += AngleDelta;
        LeftBuffer[sample] = CurrentSample * level;
        RightBuffer[sample] = CurrentSample * level;

    }

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    VolumeSlider.setBounds(100, 40, 150, 20);

    VolumeSlider.onValueChange = [this]
    {
        level = (float)VolumeSlider.getValue();
    };



    FrequencySlider.setBounds(100, 120, 150, 20);

    FrequencySlider.onValueChange = [this]
    {
        if (CurrentSampleRate)
        {
            updateAngleData();
        }
    };
        
    

}

void MainComponent::updateAngleData()
{
    auto CyclesPerSample = FrequencySlider.getValue() / CurrentSampleRate;
    AngleDelta = CyclesPerSample * 2.0 * MathConstants<double>::pi;

}
