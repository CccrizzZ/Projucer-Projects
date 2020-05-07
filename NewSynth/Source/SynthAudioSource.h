#pragma once
#include "SineWaveSound.h"
#include "SineWaveVoice.h"

class SynthAudioSource : public AudioSource
{
public:
	SynthAudioSource(MidiKeyboardState & keyState) : keyboardState(keyState) 
	{
		voice = 1;

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

		midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);

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

	void setVoice(int newVoice)
	{
		
		synth.clearVoices();
		synth.clearSounds();

		for (auto i = 0; i <= newVoice; i++)
		{
			synth.addVoice(new SineWaveVoice());
		}

		synth.addSound(new SineWaveSound());
	}

private:
	
	// external midi signal 
	MidiMessageCollector midiCollector;


	// keyboard
	MidiKeyboardState& keyboardState;
	
	// synth
	Synthesiser synth;
	
	
	// voice
	int voice;
};

