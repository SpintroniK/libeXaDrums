/*
 * AlsaParams.h
 *
 *  Created on: 2 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_SOUND_ALSAPARAMS_H_
#define RASPIDRUMS_SOURCE_SOUND_ALSAPARAMS_H_


#include "alsa/asoundlib.h"

#include <string>

namespace Sound
{

	struct AlsaParams
	{
		std::string				device;
		snd_pcm_t*				handle;
		snd_pcm_hw_params_t* 	hwParams;
		snd_pcm_sw_params_t* 	swParams;

		bool					capture;

		snd_pcm_format_t 		format;
		unsigned int 			sampleRate;
		unsigned int 			nChannels;
		unsigned int 			bufferTime;
		unsigned int 			periodTime;

		snd_pcm_sframes_t		bufferSize;
		snd_pcm_sframes_t		periodSize;

		_snd_pcm_access			access;

		short*					buffer;

	};

}

#endif /* RASPIDRUMS_SOURCE_SOUND_ALSAPARAMS_H_ */
