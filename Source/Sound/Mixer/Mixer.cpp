/*
 * Mixer.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Mixer.h"


#include <algorithm>

namespace Sound
{

	Mixer::Mixer()
	{

		// Set sounds states to false by default
		for(auto& s : soundsStates)
		{
			s.store(false);
		}


		return;
	}

	Mixer::~Mixer()
	{

		return;
	}



	void Mixer::PlaySound(int id, float volume)
	{


		auto s = std::find_if(playList.begin(), playList.end(), [&id](std::pair<int, float>& s) { return id == s.first; });

		int index;

		if(s != std::end(playList))
		{
			// The sound is already in playList
			soundBank->sounds[s->first].Seek(0);
			s->second = volume;

			index = s - playList.begin();
		}
		else
		{
			// Add sound to playList
			playList.push_back(std::pair<int, float>(id, volume));

			if(playList.size() < nbStates)
			{
				index = playList.size() - 1;
			}
			else
			{
				throw -1;
			}

		}

		// Update sound state
		soundsStates[index].store(true);

		return;
	}

	void Mixer::StopSound(int id)
	{

		// Find sound in the play list
		auto s = std::find_if(playList.begin(), playList.end(), [&id](std::pair<int, float>& s) { return id == s.first; });

		if(s != playList.end())
		{
			soundsStates[s - playList.begin()].store(false);
		}

		return;
	}


	void Mixer::Mix(std::vector<short>& buffer) noexcept
	{


		// Fill buffer with zeros
		std::fill(buffer.begin(), buffer.end(), 0);

		std::size_t periodSize = buffer.size();

		// Mix sounds
		for(std::size_t si = 0; si < playList.size(); si++)
		{
			if(soundsStates[si].load())
			{

				const auto& s = playList[si];
				Sound& sound = soundBank->sounds[s.first];

				if(sound.HasMoreData(periodSize))
				{

					const float volume = sound.GetVolume();
					const float mix_volume = s.second;

					if(sound.IsLoop())
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
		}


		return;
	}




}
