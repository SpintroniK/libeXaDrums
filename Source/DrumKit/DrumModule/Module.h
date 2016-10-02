/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_

#include "../../Sound/SoundProcessor/SoundProcessor.h"
#include "../../Sound/Mixer/Mixer.h"
#include "../../Sound/SoundBank/SoundBank.h"

#include "../../Metronome/Metronome.h"

#include "../Triggers/TriggerManager.h"

#include "../Kits/KitManager.h"
#include "../Kits/Kit.h"

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>
#include <functional>


namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, std::shared_ptr<Sound::Mixer> mixer, std::shared_ptr<Metronome> metro);
		virtual ~Module();

		// Kit
		void SaveKitConfig(int id) const { kits[id].Save(); };
		bool DeleteKit(const int& id);
		void SelectKit(std::size_t id);
		int GetNumKits() const { return (int) kits.size(); };
		std::string GetKitNameById(int id) const;

		// Instrument
		void SetInstrumentVolume(int id, float volume) { kits[kitId].SetInstrumentVolume(id, volume); };
		float GetInstrumentVolume(int id) const { return kits[kitId].GetInstrumentVolume(id); };
		std::string GetInstrumentName(std::size_t id) const;
		int GetNumInstruments() const { return kits[kitId].GetNumInstruments(); };

		// Module
		void Start();
		void Stop();
		void GetDirectory(std::string& dir) const;

		// Metronome
		void EnableMetronome(bool enable);
		void ChangeTempo(int tempo);


	private:

		void LoadKits();
		void Run();
		void CreateTriggers(std::vector<TriggerParameters> const& trigParams);
		bool IsMetronomeEnabled() const;


		// Module
		std::string directory;
		std::thread playThread;

		// Kits
		KitManager kitManager;
		int kitId;
		std::vector<Kit> kits;
		std::atomic<bool> isPlay;

		// Triggers
		std::vector<TriggerPtr> triggers;

		// Sound
		std::shared_ptr<Sound::SoundBank> soundBank;
		std::shared_ptr<Sound::SoundProcessor> soundProc;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<Metronome> metronome;

		int metronomeSoundId;
		bool isMetronomeEnabled;

	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
