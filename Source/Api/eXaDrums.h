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

using namespace Sound;

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
		void EnableMetronome(bool enable) { drumModule->EnableMetronome(enable); }
		void RestartMetronome() { drumModule->RestartMetronome(); }
		void ChangeTempo(int tempo) { drumModule->ChangeTempo(tempo); }

		int GetNumClickTypes() const { return int(Util::Enums::GetClickTypes().size()); }
		void GetClickTypeById(int id, char* kitName, int& nameLength) const;
		void SetClickType(int id) { metronome->SetClickType(Util::Enums::GetClickTypes()[id]); }
		int GetClickTypeId() const;

		int GetNumRhythms() const { return (int)this->metronome->GetRhythmList().size(); }
		void GetRhythmList(int* data) const;
		int GetRhythm() const { return this->metronome->GetRhythm(); }
		void SetRhythm(int rhythm) { this->metronome->SetRhythm(rhythm); }

		int GetNumBpmeas() const { return (int)this->metronome->GetBpmeasList().size(); }
		void GetBpmeasList(int* data) const;
		int GetBpmeas() const { return this->metronome->GetBpmeas(); }
		void SetBpmeas(int bpmeas) { this->metronome->SetBpmeas(bpmeas); }


		// Kits
		void SelectKit(int id);
		void SaveKitConfig(int id) const { drumModule->SaveKitConfig(id); }
		bool DeleteKit(const int& id) { return drumModule->DeleteKit(id); }
		int GetNumKits() const { return drumModule->GetNumKits(); }
		void GetKitNameById(int id, char* kitName, int& nameLength);

		// Instruments
		void SetInstrumentVolume(int id, int volume);
		int GetInstrumentVolume(int id) const;
		int GetNumInstruments() const { return drumModule->GetNumInstruments(); }
		void GetInstrumentName(int id, char* name, int& nameLength);

	private:

		void CppStringToC(std::string input, char* str, int& length) const;

		std::unique_ptr<DrumKit::Module> drumModule;

		std::unique_ptr<Alsa> alsa;
		std::shared_ptr<Mixer> mixer;
		std::shared_ptr<Metronome> metronome;

		std::atomic<bool> isStarted;


	};


}

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
