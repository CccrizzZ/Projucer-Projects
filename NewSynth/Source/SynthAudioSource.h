#pragma once
#include "SineWaveSound.h"
#include "SineWaveVoice.h"

class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState & keyState) : keyboardState(keyState) 
	{

		for (auto i = 0; i < voice; ++i)
		{
			synth.addVoice(new SineWaveVoice());
		}
		synth.addSound(new SineWaveSound());
	}

	void setUsingWaveSound()
	{
		synth.clearSounds();
	}

	void prepareToPlay(int, double sampleRate) override
	{
		synth.setCurrentPlaybackSampleRate(sampleRate);

		midiCollector.reset(sampleRate);
	}



	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override
	{
		bufferToFill.clearActiveBufferRegion();

		// process incoming midi
		MidiBuffer incomingMidi;
		keyboardState.processNextMidiBuffer(
			incomingMidi, 
			bufferToFill.startSample, 
			bufferToFill.numSamples,
			true
		);
		
		// render next synth block
		synth.renderNextBlock(
			*bufferToFill.buffer, 
			incomingMidi, 
			bufferToFill.startSample, 
			bufferToFill.numSamples
		);

	}

	MidiMessageCollector* getMidiCollector()
	{
		return &midiCollector;
	}

	void releaseResources() override {};
private:
	MidiMessageCollector midiCollector;


	MidiKeyboardState& keyboardState;
	Synthesiser synth;
	int voice = 4;
};

