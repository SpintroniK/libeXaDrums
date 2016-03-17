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
#include <functional>

namespace Sound
{

	class Mixer
	{

	public:

		Mixer();
		virtual ~Mixer();

		void Mix();
		void SetAlsaParameters(AlsaParams const& alsaParameters);

	private:

		AlsaParams alsaParams;

		//mutable std::mutex mixerMutex;

	};

}

#endif /* MIXER_H_ */
