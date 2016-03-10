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
		//std::lock_guard<std::mutex> lock(mixerMutex);

		// Fill buffer with zeros
		std::fill(alsaParams->buffer.begin(), alsaParams->buffer.begin() + alsaParams->periodSize, 0);


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



		return;
	}




}
