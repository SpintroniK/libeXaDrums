/*
 * SoundState.h
 *
 *  Created on: 30 Jul 2017
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDSTATE_H_
#define SOURCE_SOUND_SOUNDSTATE_H_

#include <atomic>

namespace Sound
{

	struct SoundState
	{

		SoundState() : id(0), volume(0.), index(0)
		{
			isPlaying.store(false);
		}

		SoundState(int i, float v, bool ip) : id(i), volume(v), index(0)
		{
			isPlaying.store(ip);
		}

		SoundState(const SoundState& s) : id(s.id), volume(s.volume), index(s.index)
		{
			isPlaying.store(s.isPlaying.load());
		}

		int id;
		float volume;
		std::size_t index;
		std::atomic<bool> isPlaying;

	};

}

#endif /* SOURCE_SOUND_SOUNDSTATE_H_ */
