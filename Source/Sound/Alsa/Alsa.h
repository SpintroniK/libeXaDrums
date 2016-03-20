/*
 * Alsa.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef ALSA_H_
#define ALSA_H_

#define ALSA_PCM_NEW_HW_PARAMS_API

#include "../Mixer/Mixer.h"
#include "AlsaParams.h"

#include <alsa/asoundlib.h>

#include <thread>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

namespace Sound
{


	class Alsa
	{

	public:

		Alsa(AlsaParams& parameters, std::shared_ptr<Mixer> const& mixer);
		virtual ~Alsa();


		void Start();
		void Stop();


	private:

		int SetHwParams();
		int SetSwParams();

		void StartPlayback();
		void StopPlayback();
		void Playback();

		void StartRecord();
		void StopRecord();
		void Record();

		void XrunRecovery(int& err);

		std::thread playThread;
		std::thread recordThread;

		AlsaParams params;

		std::shared_ptr<Mixer> mixer;

		std::atomic<bool> play;
		std::atomic<bool> rec;

	};

}


#endif /* ALSA_H_ */
