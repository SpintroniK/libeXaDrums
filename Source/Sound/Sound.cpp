/*
 * SoundSample.cpp
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#include "Sound.h"

namespace Sound
{


	Sound::Sound(int id, std::vector<short> soundData)
	: id(id),
	  volume(1.0f),
	  idx(0),
	  data(soundData)
	{

		return;
	}

	Sound::~Sound()
	{

		return;
	}

	bool Sound::HasMoreData(std::size_t length) const
	{

		if(idx + length <= data.size())
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

	void Sound::AddToIndex(int offset)
	{

		idx += offset;

		return;
	}


	void Sound::Seek(std::size_t index)
	{

		idx = index;

		return;
	}



	// PRIVATE


} /* namespace Sound */
