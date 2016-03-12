/*
 * SoundSample.h
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUND_H_
#define SOURCE_SOUND_SOUND_H_

#include <vector>
#include <algorithm>

namespace Sound
{

	class Sound
	{

	public:

		Sound(int id, std::vector<short> soundData);
		virtual ~Sound();

		void SetVolume(float volume);
		short ReadData();
		void ReadChunk(std::vector<short>& chunk);
		bool IsFinished() const;
		void SeekBeg();

		int GetId() const { return id; };

	private:

		int id;
		float volume;
		std::size_t idx;
		std::vector<short> data;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUND_H_ */
