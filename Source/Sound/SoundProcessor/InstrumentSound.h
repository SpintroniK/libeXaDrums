/*
 * InstrumentSound.h
 *
 *  Created on: 15 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_INSTRUMENTSOUND_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_INSTRUMENTSOUND_H_


#include "InstrumentSoundType.h"

#include <vector>

namespace Sound
{

	struct InstrumentSound
	{

		int id;
		std::vector<short> soundData;
		InstrumentSoundType type;

	};



}


#endif /* SOURCE_SOUND_SOUNDPROCESSOR_INSTRUMENTSOUND_H_ */
