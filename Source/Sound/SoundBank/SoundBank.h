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
#include <fstream>

#include <dirent.h>

namespace Sound
{

	class Mixer;

	class SoundBank
	{

	friend class Mixer;

	public:

		SoundBank(std::string dataFolder);
		virtual ~SoundBank();

		int LoadSound(std::string filename);
		int LoadSound(std::string filename, float volume);
		int AddSound(std::vector<short>& soundData);
		int AddSound(std::vector<short>& soundData, float volume);
		void LoopSound(int id, bool s) { sounds[id].SetLoop(s); }
		void Clear() { sounds.clear(); }

		void SetSoundVolume(int id, float volume) { sounds[id].SetVolume(volume); }

		const Sound& GetSound(int id) const { return sounds[id]; }


	private:

		void LoadSounds();

		std::string soundBankFolder;
		std::vector<std::string> soundsPaths;
		std::vector<Sound> sounds;


	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_ */
