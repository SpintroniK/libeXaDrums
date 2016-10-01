/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_
#define LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_

#include "../Sound/Alsa/Alsa.h"
#include "../Sound/Alsa/AlsaParameters.h"
#include "../Sound/Mixer/Mixer.h"
#include "../Metronome/Metronome.h"
#include "../DrumKit/DrumModule/Module.h"

#include "../Util/Enums.h"

#include <string>
#include <vector>
#include <memory>
#include <atomic>

#include <cmath>

namespace eXaDrumsApi
{

	class eXaDrums
	{

	public:

		eXaDrums(const char* dataLocation);
		~eXaDrums();

		// eXaDrums
		bool IsStarted() const { return isStarted; }

		// Module
		void Start();
		void Stop();

		// Metronome
		void EnableMetronome(bool enable) { drumModule->EnableMetronome(enable); };
		void ChangeTempo(int tempo) { drumModule->ChangeTempo(tempo); };
		int GetNumClickTypes() const { return int(Util::Enums::GetClickTypes().size()); };
		void GetClickTypeById(int id, char* kitName, int& nameLength) const;


		// Kits
		void SelectKit(int id);
		void SaveKitConfig(int id) const { drumModule->SaveKitConfig(id); };
		bool DeleteKit(const int& id) { return drumModule->DeleteKit(id); };
		int GetNumKits() const { return drumModule->GetNumKits(); };
		void GetKitNameById(int id, char* kitName, int& nameLength);

		// Instruments
		void SetInstrumentVolume(int id, int volume);
		int GetInstrumentVolume(int id) const;
		int GetNumInstruments() const { return drumModule->GetNumInstruments(); };
		void GetInstrumentName(int id, char* name, int& nameLength);

	private:

		void CppStringToC(std::string input, char* str, int& length) const;

		std::unique_ptr<DrumKit::Module> drumModule;

		Sound::AlsaParams alsaParams;
		std::unique_ptr<Sound::Alsa> alsa;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<DrumKit::Metronome> metronome;

		std::atomic<bool> isStarted;


	};


}

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
