/*
 * SoundProcessor.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#include "SoundProcessor.h"

namespace Sound
{

	SoundProcessor::SoundProcessor() : sounds(), durations(), alsaParams()
	{

		sounds.clear();
		durations.clear();

	}

	SoundProcessor::~SoundProcessor()
	{
		sounds.clear();
		durations.clear();

	}


	void SoundProcessor::SetAlsaParameters(AlsaParams* alsaParameters)
	{

		this->alsaParams = alsaParameters;

		return;
	}

	void SoundProcessor::SetInstrumentSounds(std::vector<short> data, unsigned int duration)
	{

		this->sounds.push_back(data);
		this->durations.push_back(duration);

		return;
	}


	void SoundProcessor::AddSound(int id, float volume)
	{

		std::lock_guard<std::mutex> lock(soundProcMutex);

		/*
		 * Not needed anymore, but left here as a reminder in RaspiDrums
		 * Needs to be tested...
		 */
		//Test if the sound has already been added to the mixer
		std::vector<SampleInfo>::iterator iter =	std::find_if(soundList.begin(), soundList.end(),
				[id](const SampleInfo& sound) { return sound.id == id; });

		// Find sound's position in the vector
		size_t i = std::distance(soundList.begin(), iter);

		if(i != soundList.size())
		{
			// The sound is already in the sound list, so we need to rewind it
			soundList[i].index = 0;
			// We also have to make sure to play the sound with the new volume
			soundList[i].volume = volume;

		}
		else
		{

			SampleInfo sample;

			sample.id = id;
			sample.index = 0;
			sample.volume = volume;

			soundList.push_back(sample);
		}

		return;
	}

	void SoundProcessor::GetSamples(std::vector<std::vector<short>>& samples)
	{


		for(size_t j = 0; j < soundList.size(); j++)
		{

			std::vector<short> buffer(alsaParams->periodSize);
			int instrumentId = soundList[j].id;

			for(int i = 0; i < alsaParams->periodSize; i++)
			{
				buffer[i] = soundList[j].volume * sounds[instrumentId][soundList[j].index + i];
			}

			soundList[j].index += alsaParams->periodSize;

			this->sampleList.push_back(buffer);
		}

		samples.swap(this->sampleList);

		return;

	}

	void SoundProcessor::DumpSamples()
	{

		// Delete the sounds that finished playing
		std::function<bool(SampleInfo)> f = [this](SampleInfo sample)
		{
			return (sample.index >= durations[sample.id]);
		};
		soundList.erase(std::remove_if(soundList.begin(), soundList.end(), f), soundList.end());

		//sampleList.clear();

		return;
	}

} /* namespace Sound */
