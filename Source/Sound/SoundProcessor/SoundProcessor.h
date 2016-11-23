/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../Sound.h"


namespace Sound
{

	class SoundProcessor
	{

	public:

		static Sound Muffle(const Sound& sound, float m);


	private:

		SoundProcessor() {};
		virtual ~SoundProcessor() {};


	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
