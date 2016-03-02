/*
 * Mixer.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Mixer.h"

namespace Sound
{

	Mixer::Mixer(std::shared_ptr<SoundProcessor> const& soundProc)
	:  soundProc(soundProc), alsaParams()
	{

		return;
	}

	Mixer::~Mixer()
	{


		return;
	}

	void Mixer::SetAlsaParameters(AlsaParams* alsaParameters)
	{

		this->alsaParams = alsaParameters;

		return;
	}

	void Mixer::Mix()
	{

		// Prevent other threads to alter the soundList vector
		std::lock_guard<std::mutex> lock(mixerMutex);

		// Fill buffer with zeros
		std::fill(alsaParams->buffer.begin(), alsaParams->buffer.begin() + alsaParams->periodSize, 0);



		/*
		std::function<void(std::vector<short>)> mix = [this](std::vector<short> data)
		{
			std::transform(data.cbegin(), data.cend(), this->alsaParams->buffer.cbegin(), this->alsaParams->buffer.begin(), std::plus<short>());
		};

		std::for_each(samples.cbegin(), samples.cend(), mix);
		*/

		const std::vector<int>& playList = soundProc->GetPlayList();


		std::vector<short> chunk(alsaParams->periodSize);

		// Mix sounds
		for(std::size_t i = 0; i < playList.size(); i++)
		{

			soundProc->ReadSoundChunk(i, chunk);

			for(int j = 0; j < alsaParams->periodSize; j++)
			{
				this->alsaParams->buffer[j] += chunk[j];
			}

			/*
			for(int j = 0; j < alsaParams->periodSize; j++)
			{
				this->alsaParams->buffer[j] += soundProc->ReadSoundData(i);
			}
			*/

		}


		soundProc->UpdatePlayList();

/*
		// If there are sounds to mix
		if(sampleList.size() > 0)
		{

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
			std::function<bool(SampleInfo)> f = [this](SampleInfo sample)
			{
				return (sample.index >= soundParameters[sample.id].length);
			};
			std::vector<SampleInfo>::iterator n =  std::remove_if(sampleList.begin(), sampleList.end(), f);
			sampleList.erase(n, sampleList.end());


		}*/

		return;
	}




}
