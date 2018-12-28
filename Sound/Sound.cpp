/*
 * SoundSample.cpp
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#include "Sound.h"

#include <chrono>

using namespace std::chrono;

namespace Sound
{

	Sound::Sound() : Sound(std::vector<short>{})
	{

		return;
	}

	Sound::Sound(Sound& s) : Sound()
	{

		swap(*this, s);

		return;
	}

	Sound::Sound(Sound&& s) : Sound()
	{

		swap(*this, s);

		return;
	}


	Sound::Sound(int id, const std::vector<short>& soundData, float vol)
	: id(id), loop(false), data(soundData), length(data.size())
	{

		volume.store(vol);
		idx.store(0);

		lastStartTime.store(time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch().count(), std::memory_order_relaxed);

		return;
	}


	Sound::Sound(int id, const std::vector<short>& soundData) : Sound(id, soundData, 1.0f)
	{

		return;
	}

	Sound::Sound(const std::vector<short>& soundData, float volume) : Sound(-1, soundData, volume)
	{

		return;
	}

	Sound::Sound(const std::vector<short>& soundData) : Sound(-1, soundData, 1.0f)
	{

		return;
	}

	Sound::~Sound()
	{

		return;
	}



	bool Sound::HasMoreData(std::size_t index, std::size_t length) const
	{

		if(loop) return true;

		if(index + length <= data.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Sound::SetVolume(float volume)
	{

		float newVolume = std::min<float>(std::max<float>(0., volume), 1.);

		this->volume.store(newVolume);

		return;
	}

	void Sound::SetStartTime()
	{

		this->lastStartTime.store(time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch().count(), std::memory_order_relaxed);

		return;
	}

	/*void Sound::AddToIndex(int offset)
	{

		if(!HasMoreData(offset))
		{
			idx.store(0);
		}
		else
		{

			long prevIdx = idx.fetch_add(offset);

			if(prevIdx % length < offset)
			{
				this->lastStartTime.store(time_point_cast<microseconds>(high_resolution_clock::now()).time_since_epoch().count());
			}

		}

		return;
	}*/


	// PRIVATE


} /* namespace Sound */
