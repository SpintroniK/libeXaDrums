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

#include <string>
#include <vector>
#include <memory>
#include <atomic>

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

		// Kits
		void SelectKit(int id);
		int GetNumKits() const { return drumModule->GetNumKits(); }
		void GetKitNameById(int id, char* kitName, int& nameLength);

		// Instruments
		int GetNumInstruments() const { return drumModule->GetNumInstruments(); }
		void GetInstrumentName(int id, char* name, int& nameLength);
		void SetInstrumentVolume(int id, float volume) { drumModule->SetInstrumentVolume(id, volume); }

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
