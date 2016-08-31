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

#include "../Kits/KitManager.h"
#include "../Kits/Kit.h"

#include "../Instruments/InstrumentParameters.h"
#include "../Instruments/Instrument.h"
#include "../Instruments/Drums/TestDrum.h"
#include "../Triggers/TriggerType.h"
#include "../Triggers/Trigger.h"
#include "../Triggers/DiscreteTrigger.h"

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>
#include <functional>
#include <utility>



namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, std::shared_ptr<Sound::Mixer> mixer, std::shared_ptr<Metronome> metro);
		virtual ~Module();

		// Kit
		void SelectKit(std::size_t id);
		int GetNumKits() const { return (int) kits.size(); }
		std::string GetKitNameById(int id) const;

		// Instrument
		std::string GetInstrumentName(std::size_t id) const;
		int GetNumInstruments() const { return kits[kitId].GetNumInstruments(); }
		void SetInstrumentVolume(int id, float volume);

		// Module
		void Start();
		void Stop();
		void GetDirectory(std::string& dir) const;


	private:

		void LoadKits();
		void Run();
		void CreateTriggers();
		void CreateInstruments();

		int kitId;

		std::shared_ptr<Sound::SoundBank> soundBank;

		KitManager kitManager;
		KitParameters kitParameters;
		std::vector<Kit> kits;

		std::string directory;

		std::vector<InstrumentPtr> instruments;
		std::vector<TriggerParameters> triggersParameters;

		std::thread playThread;
		std::atomic<bool> isPlay;
		std::shared_ptr<Sound::SoundProcessor> soundProc;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<Metronome> metronome;

		std::vector<TriggerPtr> triggers;


	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
