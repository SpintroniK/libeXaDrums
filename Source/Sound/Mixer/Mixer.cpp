/*
 * Mixer.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Mixer.h"

namespace Sound
{

	Mixer::Mixer() : playList()
	{

		return;
	}

	Mixer::~Mixer()
	{

		return;
	}


	void Mixer::SetSound(int instrumentId, SoundPtr& sound)
	{



		std::lock_guard<std::mutex> lock(mixerMutex);

		auto it = std::find_if(playList.begin(), playList.end(), [&](std::pair<int, SoundPtr> x)
		{
			return (x.first == instrumentId && x.second->GetId() == sound->GetId());
		});

		if(it != std::end(playList))
		{
			// The sound is already in playList
			(*it).second->Seek(0);
		}
		else
		{
			// Add sound to playList
			playList.push_back(std::make_pair(instrumentId, sound));
		}

		return;
	}


	void Mixer::Mix(std::vector<short>& buffer, const std::size_t periodSize)
	{

		// Fill buffer with zeros
		std::fill(buffer.begin(), buffer.begin() + periodSize, 0);

		// Mix sounds
		std::for_each(playList.begin(), playList.end(), [&buffer, &periodSize](std::pair<int, SoundPtr> x)
		{

			Sound sound = *(x.second.get());

			if(sound.IsMoreData(periodSize))
			{
				const short* data = sound.GetData();
				std::size_t idx = sound.GetIndex();
				float volume = sound.GetVolume();

				for(std::size_t i = 0; i < periodSize; i++)
				{
					buffer[i] += volume * (*(data + idx + i));
				}

				x.second->AddToIndex(periodSize);

			}
		});


		return;
	}




}
