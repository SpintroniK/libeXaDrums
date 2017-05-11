/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_

#include "../../Metronome/Metronome.h"

#include "../../IO/SensorsConfig.h"

#include "../../Sound/Mixer/Mixer.h"
#include "../../Sound/SoundBank/SoundBank.h"

#include "../Kits/Kit.h"


#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <memory>


namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, std::shared_ptr<Sound::Mixer> mixer, std::shared_ptr<Metronome> metro);
		virtual ~Module() = default;

		// Kit
		void SaveKitConfig(int id) const { kits[id].Save(); };
		std::string GetKitLocation() const { return kits[kitId].GetConfigFilePath(); };
		bool DeleteKit(const int& id);
		void SelectKit(std::size_t id);
		void ReloadKits();
		int GetKitId() const { return kitId; }
		int GetNumKits() const { return (int) kits.size(); };
		std::vector<std::string> GetKitsNames() const;
		std::vector<std::string> GetInstrumentsNames() const;

		// Instrument
		void SetInstrumentVolume(int id, float volume) { kits[kitId].SetInstrumentVolume(id, volume); };
		float GetInstrumentVolume(int id) const { return kits[kitId].GetInstrumentVolume(id); };
		int GetNumInstruments() const { return kits[kitId].GetNumInstruments(); };

		// Triggers
		void ReloadTriggers();
		std::vector<TriggerParameters> GetTriggersParameters() const { return this->triggersParameters; }
		unsigned long long GetLastTrigTime() const { return lastTrigTime.load(); }
		int GetLastTrigValue() const { return lastTrigValue.load(); }

		// Module
		void Start();
		void Stop();
		void GetDirectory(std::string& dir) const;

		// Metronome
		void EnableMetronome(bool enable);
		void ChangeTempo(int tempo);
		void ChangeVolume(int volume);
		float GetClickVolume() const;
		void RestartMetronome();
		double GetClickPosition() const;

		// Config
		IO::SensorsConfig GetSensorsConfig() const { return sensorsConfig; }

	private:

		void LoadKits();
		void LoadTriggers();
		void Run();
		void CreateTriggers(const std::vector<TriggerParameters>& trigParams);
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
		std::vector<TriggerParameters> triggersParameters;
		std::vector<TriggerPtr> triggers;
		std::atomic<long long> lastTrigTime;
		std::atomic<int> lastTrigValue;

		IO::SensorsConfig sensorsConfig;

		// Sound
		std::shared_ptr<Sound::SoundBank> soundBank;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<Metronome> metronome;

		int metronomeSoundId;
		bool isMetronomeEnabled;

	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
