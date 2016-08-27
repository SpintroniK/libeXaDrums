/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "../SoundBank/SoundBank.h"
#include "../Sound.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <memory>
#include <mutex>

namespace Sound
{

	class Mixer
	{

	public:

		Mixer();
		virtual ~Mixer();

		void PlaySound(int id);
		void LoopSound(int id);
		void StopSound(int id);

		void Mix(std::vector<short>& buffer);
		void Dump() { playList.clear(); };

		void SetSoundBank(std::shared_ptr<SoundBank> sb) { this->soundBank = sb; }

	private:

		std::shared_ptr<SoundBank> soundBank;
		std::vector<int> playList;

		mutable std::mutex mixerMutex;

	};

}

#endif /* MIXER_H_ */
