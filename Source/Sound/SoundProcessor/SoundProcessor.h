/*
 * SoundProcessor.h
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_
#define SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_


#include "../Alsa/AlsaParams.h"
#include "../SoundSample.h"

#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <memory>
#include <functional>
#include <iterator>


namespace Sound
{

	class SoundProcessor
	{

	public:

		SoundProcessor();
		virtual ~SoundProcessor();

		void SetAlsaParameters(AlsaParams* alsaParameters);
		void AddSound(int& id, std::vector<short> soundData);
		void GetPlayList(std::vector<int>& list) const;
		void UpdatePlayList();
		void PlaySound(int soundId);
		short ReadSoundData(int soundId);


	private:


		AlsaParams* alsaParams;
		std::vector<std::shared_ptr<SoundSample>> sounds;
		std::map<int, bool> playList;
		//mutable std::mutex soundProcMutex;

	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDPROCESSOR_SOUNDPROCESSOR_H_ */
