/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../SampleInfo.h"
#include "../Alsa/AlsaParams.h"

#include <mutex>
#include <vector>
#include <algorithm>
#include <functional>


namespace Sound
{

	class SoundProcessor
	{

	public:

		SoundProcessor();
		virtual ~SoundProcessor();

		void SetAlsaParameters(AlsaParams* alsaParameters);
		void SetInstrumentSounds(std::vector<short> data, unsigned int duration);

		void AddSound(int id, float volume);
		void GetSamples(std::vector<std::vector<short>>& samples);
		void DumpSamples();

	private:

		std::vector<std::vector<short>> sounds;
		std::vector<unsigned int> durations;

		std::vector<SampleInfo> soundList;
		std::vector<std::vector<short>> sampleList;

		AlsaParams* alsaParams;

		mutable std::mutex soundProcMutex;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
