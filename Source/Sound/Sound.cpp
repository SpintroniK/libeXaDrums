/*
 * SoundSample.cpp
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#include "Sound.h"

namespace Sound
{


	Sound::Sound(std::vector<short> soundData)
	: volume(1.0f),
	  idx(0),
	  data(soundData)
	{

		return;
	}

	Sound::~Sound()
	{

		return;
	}


	void Sound::SetVolume(float volume)
	{

		if(volume < 0.0f)
		{
			this->volume = 0.0f;
		}
		else if(volume > 1.0f)
		{
			this->volume = 1.0f;
		}
		else
		{
			this->volume = volume;
		}

		return;
	}

	short Sound::ReadData()
	{

		idx++;

		if(idx >= data.size())
		{
			return 0;
		}
		else
		{
			return volume*data[idx];
		}

	}

	void Sound::ReadChunk(std::vector<short>& chunk)
	{

		std::size_t length = chunk.size();

		if(idx >= data.size())
		{
			std::fill(chunk.begin(), chunk.end(), 0);
		}
		else if(idx + length >= data.size())
		{

			std::fill(chunk.begin(), chunk.end(), 0);
			std::copy(data.begin() + idx, data.end(), chunk.begin());

		}
		else
		{
			std::copy(data.begin() + idx, data.begin() + idx + length, chunk.begin());
			idx += length;
		}

		std::transform(chunk.begin(), chunk.end(), chunk.begin(), std::bind1st(std::multiplies<float>(), volume));

		return;

	}


	bool Sound::IsFinished() const
	{
		return idx >= data.size();
	}


	void Sound::SeekBeg()
	{

		idx = 0;

		return;
	}

	// PRIVATE


} /* namespace Sound */
