/*
 * AlsaParams_api.h
 *
 *  Created on: 7 Oct 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_ALSAPARAMS_API_H_
#define SOURCE_API_CONFIG_ALSAPARAMS_API_H_

#include "../../Sound/Alsa/AlsaParams.h"

#include <cstring>

namespace eXaDrumsApi
{

	struct AlsaParamsApi
	{

		AlsaParamsApi()
		{
			*this = Sound::AlsaParams();
		}

		explicit AlsaParamsApi(const Sound::AlsaParams& alsaparams)
		{
			*this = alsaparams;
		}

		explicit operator Sound::AlsaParams() const
		{
			Sound::AlsaParams alsaParams;

			alsaParams.capture = this->capture;
			alsaParams.sampleRate = this->sampleRate;
			alsaParams.nChannels = this->nChannels;
			alsaParams.bufferTime = this->bufferTime;
			alsaParams.periodTime = this->periodTime;

			alsaParams.device = this->device;

			return alsaParams;
		}


		AlsaParamsApi& operator=(const Sound::AlsaParams& alsaparams)
		{
			this->capture = alsaparams.capture;
			this->sampleRate = alsaparams.sampleRate;
			this->nChannels = alsaparams.nChannels;
			this->bufferTime = alsaparams.bufferTime;
			this->periodTime = alsaparams.periodTime;

			if(alsaparams.device.size() > sizeof(this->device))
			{
				throw -1;
			}

			std::strcpy(this->device, alsaparams.device.data());

			return *this;
		}

		bool capture;
		unsigned int sampleRate;
		unsigned int nChannels;
		unsigned int bufferTime;
		unsigned int periodTime;

		char device[64];

	};


}


#endif /* SOURCE_API_CONFIG_ALSAPARAMS_API_H_ */
