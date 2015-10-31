/*
 * Mixer.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Mixer.h"

namespace Sound
{

	Mixer::Mixer() : soundParameters(), alsaParams()
	{

		return;
	}

	Mixer::~Mixer()
	{


		return;
	}

	void Mixer::SetSoundParameters(std::vector<DrumKit::SoundParams> soundParams)
	{

		soundParameters = soundParams;

		return;
	}

	void Mixer::SetAlsaParameters(AlsaParams* alsaParameters)
	{

		this->alsaParams = alsaParameters;

		return;
	}

	void Mixer::AddToMixer(int id, float volume)
	{

		// Prevent other threads to alter the soundList vector
		std::lock_guard<std::mutex> lock(mixerMutex);

		/*
		 * Not needed anymore, but left here as a reminder
		 *
		 * // Test if the sound has already been added to the mixer
		std::vector<SoundInfo>::iterator iter =	std::find_if(soundList.begin(), soundList.end(),
				[id](const SoundInfo& sound) { return sound.id == id; });

		// Find sound's position in the vector
		size_t i = std::distance(soundList.begin(), iter);

		if(i != soundList.size())
		{
			// The sound is already in the sound list, so we need to rewind it
			soundList[i].index = 0;
			// We also have to make sure to play the sound with the new volume
			soundList[i].volume = volume;

		}
		else*/
		{
			// The sound needs to be added to the sound list

			SampleInfo sample;

			sample.id = id;
			sample.index = 0;
			sample.volume = volume;

			sampleList.push_back(sample);
		}

		return;
	}


	void Mixer::Mix()
	{

		// Prevent other threads to alter the soundList vector
		std::lock_guard<std::mutex> lock(mixerMutex);

		// Fill buffer with zeros
		std::fill(alsaParams->buffer.begin(), alsaParams->buffer.begin() + alsaParams->periodSize, 0);

		// If there are sounds to mix
		if(sampleList.size() > 0)
		{

			std::vector<size_t> soundsToDelete;

			// Browse sound list
			for(size_t id = 0; id < sampleList.size(); id++)
			{

				int soundId = sampleList[id].id;
				int soundIndex = sampleList[id].index;

				// Mix sound
				for(int i = 0; i < alsaParams->periodSize; i++)
				{
					alsaParams->buffer[i] += sampleList[id].volume * soundParameters[soundId].data[soundIndex + i];
				}

				// Update sound index
				sampleList[id].index += alsaParams->periodSize;

			}

			// Delete the sounds that finished playing
			auto f = [this](SampleInfo sample) { return (sample.index >= soundParameters[sample.id].length); };
			std::vector<SampleInfo>::iterator n =  std::remove_if(sampleList.begin(), sampleList.end(), f);
			sampleList.erase(n, sampleList.end());

		}

		return;
	}




}
