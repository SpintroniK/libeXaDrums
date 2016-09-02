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


	void Mixer::PlaySound(int id, float volume)
	{

		std::lock_guard<std::mutex> lock(mixerMutex);

		auto it = std::find_if(playList.begin(), playList.end(), [&id](std::pair<int, float>& s) { return id == s.first; });

		if(it != std::end(playList))
		{
			// The sound is already in playList
			soundBank->sounds[(*it).first].Seek(0);
			(*it).second = volume;
		}
		else
		{
			// Add sound to playList
			playList.push_back(std::pair<int, float>(id, volume));
		}

		return;
	}


	void Mixer::Mix(std::vector<short>& buffer)
	{

		// Fill buffer with zeros
		std::fill(buffer.begin(), buffer.end(), 0);

		std::size_t periodSize = buffer.size();

		// Mix sounds
		for(std::pair<int, float> const& s : playList)
		{

			Sound& sound = soundBank->sounds[s.first];

			if(sound.HasMoreData(periodSize))
			{

				const float volume = sound.GetVolume();
				const float mix_volume = s.second;

				if(sound.isLoop())
				{
					for(std::size_t i = 0; i < periodSize; i++)
					{
						buffer[i] += volume * mix_volume * sound.GetValue(i);
					}
				}
				else
				{
					const short* data = sound.GetData();
					const std::size_t idx = sound.GetIndex();

					for(std::size_t i = 0; i < periodSize; i++)
					{
						buffer[i] += volume * mix_volume *(*(data + idx + i));
					}
				}

				sound.AddToIndex(periodSize);
			}
		}


		return;
	}




}
