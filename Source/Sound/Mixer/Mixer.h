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
#include <memory>
#include <atomic>
#include <array>


namespace Sound
{

	class Mixer
	{

	public:

		Mixer();
		virtual ~Mixer();

		void PlaySound(int id, float volume);
		void LoopSound(int id, float volume);
		void StopSound(int id);

		void Mix(std::vector<short>& buffer) noexcept;
		void Clear() { playList.clear(); };

		void SetSoundBank(std::shared_ptr<SoundBank> sb) { this->soundBank = sb; }

	private:

		static const std::size_t nbStates = 128;

		std::shared_ptr<SoundBank> soundBank;
		std::vector<std::pair<int, float>> playList;
		std::array<std::atomic<bool>, nbStates> soundsStates;

	};

}

#endif /* MIXER_H_ */
