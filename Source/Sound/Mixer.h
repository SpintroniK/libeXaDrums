/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "AlsaParams.h"
#include "SoundInfo.h"

#include "../DrumKit/Module.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include <mutex>

namespace Sound
{

	class Mixer
	{

	public:

		Mixer(const std::vector<DrumKit::SoundParams>& soundParams, const AlsaParams& params);
		virtual ~Mixer();

		void Mix();
		void AddToMixer(int id, float volume);

	private:

		const std::vector<DrumKit::SoundParams>& soundParameters;
		const AlsaParams& alsaParams;

		mutable std::mutex mixerMutex;

		std::vector<SoundInfo> soundList;

	};

}

#endif /* MIXER_H_ */
