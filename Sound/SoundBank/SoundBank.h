/*
 * SoundBank.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_
#define SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_

#include "../Sound.h"

#include <string>
#include <vector>

namespace Sound
{

	class Mixer;

	class SoundBank
	{

	friend class Mixer;

	public:

		explicit SoundBank(const std::string& dataFolder) noexcept;
		virtual ~SoundBank();

		static std::vector<std::string> GetSoundFiles(const std::string& dataFolder);

		int LoadSound(const std::string& filename);
		int LoadSound(const std::string& filename, float volume);
		int AddSound(const std::vector<short>& soundData);
		int AddSound(const std::vector<short>& soundData, float volume);
		int AddSound(Sound&& sound, float volume);
		void DeleteSound(int id);
		void LoopSound(int id, bool s);
		void Clear() noexcept { std::vector<Sound>().swap(sounds); }

		void SetSoundVolume(int id, float volume) { sounds[id].SetVolume(volume); }

		const Sound& GetSound(int id) const { return sounds[id]; }


	private:


		std::string soundBankFolder;
		std::vector<Sound> sounds;


	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_ */
