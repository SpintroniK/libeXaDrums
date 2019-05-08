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


#include <thread>
#include <atomic>
#include <vector>

namespace Sound
{


	class Alsa
	{

	public:

		Alsa(const AlsaParams& parameters, std::shared_ptr<Mixer> const& mixer);
		virtual ~Alsa();

		static std::vector<std::pair<std::string, std::string>> GetDevices(const snd_pcm_stream_t type = SND_PCM_STREAM_PLAYBACK);

		void Start();
		void Stop();

		std::string GetDeviceName() const noexcept { return deviceName; }
		AlsaParams GetParameters() const { return params; }


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
		std::string deviceName;

		std::shared_ptr<Mixer> mixer;

		std::atomic<bool> play;
		std::atomic<bool> rec;

	};

}


#endif /* ALSA_H_ */
