/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "../Sound.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <mutex>

namespace Sound
{

	class Mixer
	{

	public:

		Mixer();
		virtual ~Mixer();

		void PlaySound(int instrumentId, SoundPtr& sound);
		void Mix(std::vector<short>& buffer);
		void Dump() { playList.clear(); };

		void SetPeriodSize(std::size_t pSize) { this->periodSize = pSize; }

	private:

		std::size_t periodSize;
		std::vector<std::pair<int, SoundPtr>> playList;
		mutable std::mutex mixerMutex;

	};

}

#endif /* MIXER_H_ */
