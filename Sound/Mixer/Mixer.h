/*
 * Mixer.h
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "../SoundBank/SoundBank.h"
#include "../SoundState.h"
#include "../Sound.h"

#include <vector>
#include <array>
#include <memory>
#include <atomic>


namespace Sound
{

	class Mixer
	{

	public:

		Mixer() noexcept;
		virtual ~Mixer();

		void PlaySound(int id, float volume);
		void LoopSound(int id, float volume);
		void StopSound(int id);

		void Mix(std::vector<short>& buffer) noexcept;
		void Clear() noexcept;

		void SetSoundBank(std::shared_ptr<SoundBank>& sb) noexcept { this->soundBank = sb; }

	private:


		std::shared_ptr<SoundBank> soundBank;
		std::array<SoundState, 256> playList;
		std::atomic<size_t> playListIndex{0};

	};

}

#endif /* MIXER_H_ */
