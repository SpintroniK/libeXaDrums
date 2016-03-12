/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../Alsa/AlsaParams.h"
#include "../Sound.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <memory>
#include <functional>


namespace Sound
{

	class SoundProcessor
	{

	public:

		SoundProcessor();
		virtual ~SoundProcessor();

		void SetAlsaParameters(AlsaParams* alsaParameters);
		//void AddSound(int& id, std::vector<short> soundData);
		const std::vector<int>& GetPlayList() const;
		void UpdatePlayList();
		void PlaySound(int soundId);
		short ReadSoundData(int soundId);
		void ReadSoundChunk(int soundId, std::vector<short>& chunk);


	private:


		AlsaParams* alsaParams;
		std::vector<Sound> sounds;
		std::vector<int> playList;
		//mutable std::mutex soundProcMutex;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
