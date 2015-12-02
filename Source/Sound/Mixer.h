/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "SoundProcessor/SoundProcessor.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <functional>

namespace Sound
{

	class Mixer
	{

	public:

		Mixer(std::shared_ptr<SoundProcessor> const& soundProc);
		virtual ~Mixer();

		void Mix();
		void SetAlsaParameters(AlsaParams* alsaParameters);
		void SetSoundParameters(std::vector<DrumKit::SoundParams> soundParams);

	private:

		std::shared_ptr<SoundProcessor> const& soundProc;

		AlsaParams* alsaParams;

		mutable std::mutex mixerMutex;

	};

}

#endif /* MIXER_H_ */
