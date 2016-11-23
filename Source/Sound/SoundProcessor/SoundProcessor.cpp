/*
 * SoundProcessor.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */


#include "SoundProcessor.h"

#include <vector>
#include <algorithm>

#include <cmath>

namespace Sound
{


	Sound SoundProcessor::Muffle(const Sound& sound, float m)
	{

		//XXX Need to check m!

		std::vector<short> soundData = sound.GetInternalData();
		std::vector<short> newSoundData(soundData.size());

		int nm = m * soundData.size();

		for(std::size_t i = 0; i < newSoundData.size(); i++)
		{
			newSoundData[i] = soundData[i] * std::exp(-3.0f * i / nm);
		}

		return Sound(newSoundData);
	}


} /* namespace Sound */
