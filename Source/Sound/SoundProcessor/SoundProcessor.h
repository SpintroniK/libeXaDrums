/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../Alsa/AlsaParams.h"
#include "../Sound.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <memory>
#include <functional>


namespace Sound
{

	class SoundProcessor
	{

	public:

		SoundProcessor();
		virtual ~SoundProcessor();



	private:


	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
