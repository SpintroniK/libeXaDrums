/*
 * SoundSample.cpp
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#include "SoundSample.h"

namespace Sound
{

	SoundSample::SoundSample(int id, std::vector<short> soundData)
	: id(id),
	  volume(1.0f),
	  idx(0),
	  data(soundData)
	{

		return;
	}

	SoundSample::~SoundSample()
	{

		return;
	}


	void SoundSample::SetVolume(float volume)
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

	short SoundSample::ReadData()
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

	void SoundSample::ReadChunk(std::vector<short>& chunk)
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


	bool SoundSample::IsFinished() const
	{
		return idx >= data.size();
	}


	void SoundSample::SeekBeg()
	{

		idx = 0;

		return;
	}

	// PRIVATE


} /* namespace Sound */
