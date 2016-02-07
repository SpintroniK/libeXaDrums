/*
 * AlsaParameters.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_ALSA_ALSAPARAMETERS_H_
#define SOURCE_SOUND_ALSA_ALSAPARAMETERS_H_

#include "AlsaParams.h"

#include <tinyxml2.h>

#include <string>
#include <map>

namespace Sound
{

	class AlsaParameters
	{

	public:

		static void LoadAlsaParameters(std::string filePath, AlsaParams& parameters);


	private:


		AlsaParameters() {};
		virtual ~AlsaParameters() {};

		static snd_pcm_format_t GetSndFormat(std::string formatName);
		static _snd_pcm_access GetAccessType(std::string accessName);

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_ALSA_ALSAPARAMETERS_H_ */
