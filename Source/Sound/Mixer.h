/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "../DrumKit/Kit.h"
#include "Alsa/AlsaParams.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include <mutex>
#include "Alsa/AlsaParams.h"
#include "SampleInfo.h"

namespace Sound
{

	class Mixer
	{

	public:

		Mixer();
		virtual ~Mixer();

		void Mix();
		void AddToMixer(int id, float volume);
		void SetAlsaParameters(AlsaParams* alsaParameters);
		void SetSoundParameters(std::vector<DrumKit::SoundParams> soundParams);

	private:

		std::vector<DrumKit::SoundParams> soundParameters;
		AlsaParams* alsaParams;

		mutable std::mutex mixerMutex;

		std::vector<SampleInfo> sampleList;

	};

}

#endif /* MIXER_H_ */
