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
