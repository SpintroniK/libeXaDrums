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

		void SetSound(int instrumentId, SoundPtr& sound);
		void Mix(std::vector<short>& buffer, const std::size_t periodSize);

	private:

		std::vector<std::pair<int, SoundPtr>> playList;
		mutable std::mutex mixerMutex;

	};

}

#endif /* MIXER_H_ */
