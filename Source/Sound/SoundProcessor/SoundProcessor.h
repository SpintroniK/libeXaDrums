/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../../DrumKit/Kit.h"
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
		void SetSoundParameters(std::vector<DrumKit::SoundParams> soundParams);

		void AddSound(int id, float volume);
		void GetSamples(std::vector<std::vector<short>>& samples);
		void DumpSamples();

	private:


		std::vector<SampleInfo> soundList;
		std::vector<std::vector<short>> sampleList;
		std::vector<DrumKit::SoundParams> soundParameters;

		AlsaParams* alsaParams;

		mutable std::mutex soundProcMutex;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
