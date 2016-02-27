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
	  index(0),
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

		this->index++;

		if(this->index >= this->data.size())
		{
			return 0;
		}
		else
		{
			return this->data[this->index];
		}

	}

	bool SoundSample::IsFinished() const
	{
		return index >= data.size();
	}


	void SoundSample::SeekBeg()
	{

		index = 0;

		return;
	}

	// PRIVATE


} /* namespace Sound */
