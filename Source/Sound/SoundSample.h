/*
 * SoundSample.h
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDSAMPLE_H_
#define SOURCE_SOUND_SOUNDSAMPLE_H_

#include <vector>

namespace Sound
{

	class SoundSample
	{

	public:

		SoundSample(int id, std::vector<short> soundData);
		virtual ~SoundSample();

		void SetVolume(float volume);
		short ReadData();
		bool IsFinished() const;
		void SeekBeg();

		int GetId() const { return id; };

	private:

		int id;
		float volume;
		std::size_t index;
		std::vector<short> data;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDSAMPLE_H_ */
