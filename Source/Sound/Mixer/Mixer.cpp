/*
 * Mixer.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Mixer.h"

namespace Sound
{

	Mixer::Mixer()
	{

		return;
	}

	Mixer::~Mixer()
	{

		return;
	}


	void Mixer::PlaySound(int id)
	{

		std::lock_guard<std::mutex> lock(mixerMutex);

		std::vector<int>::const_iterator it = std::find_if(playList.cbegin(), playList.cend(), [&id](int i) { return id == i; });

		if(it != std::end(playList))
		{
			// The sound is already in playList
			soundBank->sounds[*it].Seek(0);
		}
		else
		{
			// Add sound to playList
			playList.push_back(id);
		}

		return;
	}


	void Mixer::Mix(std::vector<short>& buffer)
	{

		// Fill buffer with zeros
		std::fill(buffer.begin(), buffer.end(), 0);

		std::size_t periodSize = buffer.size();

		// Mix sounds
		for(int const& id : playList)
		{

			Sound& sound = soundBank->sounds[id];

			if(sound.HasMoreData(periodSize))
			{
				const short* data = sound.GetData();
				const std::size_t idx = sound.GetIndex();
				const float volume = sound.GetVolume();

				for(std::size_t i = 0; i < periodSize; i++)
				{
					buffer[i] += volume * (*(data + idx + i));
				}

				sound.AddToIndex(periodSize);
			}
		}


		return;
	}




}
