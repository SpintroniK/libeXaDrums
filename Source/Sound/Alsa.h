/*
 * Alsa.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef ALSA_H_
#define ALSA_H_

#define ALSA_PCM_NEW_HW_PARAMS_API

#include "Mixer.h"
#include "AlsaParams.h"

#include <alsa/asoundlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

#include <thread>
#include <chrono>
#include <map>
#include <iomanip>
#include <iostream>

namespace Sound
{


	class Alsa
	{

	public:

		Alsa(AlsaParams& parameters, Mixer& mixer);
		virtual ~Alsa();

		static void ReadXmlConfig(AlsaParams& params, const std::string fileLocation);

		void Start();
		void Stop();


	private:

		int 			SetHwParams();
		int 			SetSwParams();

		void 			StartPlayback();
		void 			StopPlayback();
		void 			Playback();

		void			StartRecord();
		void 			StopRecord();
		void 			Record();

		int 			XrunRecovery(int err);

		static void 	GetSndFormat(const char* fName, snd_pcm_format_t& format);
		static void 	GetAccessType(const char* aName, _snd_pcm_access& access);

		std::thread 	playThread;
		std::thread 	recordThread;

		AlsaParams& 	params;

		Mixer& 			mixer;

		bool			play;
		bool			rec;

	};

}


#endif /* ALSA_H_ */
