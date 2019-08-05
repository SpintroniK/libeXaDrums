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

	Mixer::Mixer() noexcept
	{
		return;
	}

	Mixer::~Mixer()
	{
		return;
	}



	void Mixer::PlaySound(int id, float volume)
	{


		auto s = std::find_if(playList.begin(), playList.end(), [&id](SoundState& s) 
		{ 
			return id == s.id && !s.isPlaying.load(std::memory_order_relaxed); 
		});


		if(s != playList.end())
		{
			// The sound is already in playList
			//soundBank->sounds[s->id].Seek(0);
			s->volume = volume;
			s->index = 0;
			s->isPlaying.store(true, std::memory_order_release);

		}
		else
		{
			// Add sound to playList
			//playList.emplace_back(id, volume, true);
			const auto index = playListIndex.fetch_add(1, std::memory_order_relaxed);
			
			// Protect from overflow (ignore new sound...)
			if(index >= playList.size())
			{
				return;
			}

			playList[index].id = id;
			playList[index].volume = volume;
			playList[index].isPlaying.store(true, std::memory_order_release);

		}


		return;
	}

	void Mixer::StopSound(int id)
	{

		// Stop sound in the play list

		for(auto& sound : playList)
		{
			if(sound.id == id)
			{
				sound.isPlaying.store(false, std::memory_order_relaxed);
			}
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
			if(playList[si].isPlaying.load(std::memory_order_acquire))
			{

				SoundState& soundState = playList[si];
				Sound& sound = soundBank->sounds[soundState.id];

				if(sound.HasMoreData(soundState.index, periodSize))
				{

					const float volume = sound.GetVolume();
					const float mix_volume = soundState.volume;

					if(sound.IsLoop())
					{

						std::size_t prevIdx = sound.LoadIndex();

						if(prevIdx % sound.GetLength() < periodSize)
						{
							sound.SetStartTime();
						}

						for(std::size_t i = 0; i < periodSize; i++)
						{
							buffer[i] += volume * mix_volume * sound.GetValue(i + soundState.index);
						}

						sound.StoreIndex(soundState.index);

					}
					else
					{
						const short* data = sound.GetData();
						const std::size_t idx = soundState.index;

						for(std::size_t i = 0; i < periodSize; i++)
						{
							buffer[i] += volume * mix_volume * data[idx + i];
						}
					}

					soundState.index += periodSize;
					//sound.AddToIndex(periodSize);
				}
				else
				{
					soundState.isPlaying.store(false, std::memory_order_relaxed);
				}
			}
		}


		return;
	}

	/**
	 * @brief Stops all sounds (must be done after the mixer has been stopped).
	 * 
	 */
	void Mixer::Clear() noexcept
	{ 
		playListIndex.store(0, std::memory_order_relaxed);
		for(auto& s : playList)
		{
			s.isPlaying.store(false, std::memory_order_relaxed);
		}
	}


}
