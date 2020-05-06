#pragma once



struct SineWaveVoice : public SynthesiserVoice
{
	SineWaveVoice() {};
	

	double	currentAngle = 0.0, 
			angleDelta = 0.0,
			level = 0.0, 
			tailOff = 0.0;


	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast<SineWaveSound*> (sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound*, int)override
	{
		currentAngle = 0.0;
		level = velocity * 0.15;
		tailOff = 0.0;

		auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		auto cyclesPerSample = cyclesPerSecond / getSampleRate();

		angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
	}





	void stopNote(float , bool allowTailOff) override
	{
		if (allowTailOff)
		{
			if (tailOff == 0.0)
			{
				tailOff = 1.0;
			}
		}
		else
		{
			clearCurrentNote();
			angleDelta = 0.0;

		}
	}



	void pitchWheelMoved(int newPitchWheelValue) override {};

	void controllerMoved(int controllerNumber, int newControllerValue) override {};

	
	void renderNextBlock(AudioSampleBuffer &outputBuffer, int startSample, int numSamples) override
	{
		if (angleDelta != 0.0)
		{
			if (tailOff > 0.0)
			{
				while (--numSamples >= 0)
				{
					auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);


					for (auto i = outputBuffer.getNumChannels(); --i >= 0; )
					{
						outputBuffer.addSample(i, startSample, currentSample);

					}
					currentAngle += angleDelta;
					++startSample;

					tailOff *= 0.99;

					if (tailOff <= 0.005)
					{
						clearCurrentNote();
						angleDelta = 0.0;
						break;
					}
				}
			}
			else
			{
				while (--numSamples >= 0)
				{
					auto currentSample = (float)(std::sin(currentAngle) * level);

					for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					{
						outputBuffer.addSample(i, startSample, currentSample);
					}
					currentAngle += angleDelta;
					++startSample;
				}
			}
		}
	}

};