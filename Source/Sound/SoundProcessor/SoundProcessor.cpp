/*
 * SoundProcessor.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#include "SoundProcessor.h"

namespace Sound
{

	SoundProcessor::SoundProcessor() : soundParameters(), alsaParams()
	{

	}

	SoundProcessor::~SoundProcessor()
	{

	}


	void SoundProcessor::SetAlsaParameters(AlsaParams* alsaParameters)
	{

		this->alsaParams = alsaParameters;

		return;
	}

	void SoundProcessor::SetSoundParameters(std::vector<DrumKit::SoundParams> soundParams)
	{

		soundParameters = soundParams;

		return;
	}

	void SoundProcessor::AddSound(int id, float volume)
	{

		std::lock_guard<std::mutex> lock(soundProcMutex);

		SampleInfo sample;

		sample.id = id;
		sample.index = 0;
		sample.volume = volume;

		soundList.push_back(sample);

		return;
	}

	void SoundProcessor::GetSamples(std::vector<std::vector<short>>& samples)
	{


		for(size_t j = 0; j < soundList.size(); j++)
		{

			std::vector<short> buffer(alsaParams->periodSize);

			for(int i = 0; i < alsaParams->periodSize; i++)
			{
				buffer[i] = soundList[j].volume * soundParameters[soundList[j].id].data[soundList[j].index + i];
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
			return (sample.index >= soundParameters[sample.id].length);
		};
		soundList.erase(std::remove_if(soundList.begin(), soundList.end(), f), soundList.end());

		//sampleList.clear();

		return;
	}

} /* namespace Sound */
