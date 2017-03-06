/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */


#include "Module.h"

#include "../Triggers/TriggerManager.h"
#include "../Triggers/Triggers/DiscreteTrigger.h"
#include "../Triggers/Triggers/ContinuousTrigger.h"

#include "../Kits/KitManager.h"

#include <thread>
#include <algorithm>
#include <functional>


using namespace Sound;

namespace DrumKit
{

	Module::Module(std::string dir, std::shared_ptr<Mixer> mixer, std::shared_ptr<Metronome> metro)
	: directory(dir),
	  kitManager(dir + "Kits/"),  kitId(0),
	  isPlay(false),
	  mixer(mixer),
	  metronome(metro), metronomeSoundId(-1), isMetronomeEnabled(false)
	{

		this->soundBank = std::make_shared<SoundBank>(dir);

		mixer->SetSoundBank(soundBank);


		// Load Triggers
		LoadTriggers();

		// Load all drum kits
		LoadKits();

		// Select current kit
		SelectKit(kitId);

		return;
	}


	void Module::Start()
	{

		isPlay.store(true);
		playThread = std::thread(&Module::Run, this);

		return;
	}


	void Module::Stop()
	{

		isPlay.store(false);
		playThread.join();

		mixer->Clear();

		return;
	}

	void Module::GetDirectory(std::string& dir) const
	{

		dir = this->directory;

		return;
	}


	void Module::SelectKit(std::size_t id)
	{

		if(id > kits.size())
		{
			throw -1;
		}

		// Disable previous kit
		kits[kitId].Disable();

		// Clear sound bank and mixer
		mixer->Clear();
		soundBank->Clear();

		// Update kit id
		kitId = id;

		// Enable new kit
		kits[kitId].Enable();

		if(isMetronomeEnabled)
		{
			EnableMetronome(true);
		}


		return;
	}

	std::vector<std::string> Module::GetKitsNames() const
	{

		std::vector<std::string> names;
		std::transform(kits.cbegin(), kits.cend(), std::back_inserter(names), [](const Kit& k) { return k.GetName(); });

		return names;
	}

	std::vector<std::string> Module::GetInstrumentsNames() const
	{

		const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();

		std::vector<std::string> names;
		std::transform(instruments.cbegin(), instruments.cend(), std::back_inserter(names), [](const InstrumentPtr i) { return i->GetName(); });

		return names;
	}


	bool Module::DeleteKit(const int& id)
	{

		bool isSuccess = kitManager.DeleteKit(id);

		if(isSuccess)
		{
			LoadKits();
		}

		return isSuccess;
	}

	void Module::ReloadKits()
	{

		kitManager.ReScan();
		LoadKits();

		return;
	}

	void Module::ReloadTriggers()
	{

		LoadTriggers();

		return;
	}

	void Module::EnableMetronome(bool enable)
	{

		if(enable)
		{
			metronome->GenerateClick();
			std::vector<short> data = metronome->GetData();

			metronomeSoundId = soundBank->AddSound(data, 0.5f);
			soundBank->LoopSound(metronomeSoundId, true);
			mixer->PlaySound(metronomeSoundId, 1.0f);

			isMetronomeEnabled = true;
		}
		else
		{

			if(metronomeSoundId != -1)
			{
				// Stop metronome sound
				mixer->StopSound(metronomeSoundId);
				soundBank->DeleteSound(metronomeSoundId);
			}

			isMetronomeEnabled = false;
		}


		return;
	}

	void Module::ChangeTempo(int tempo)
	{

		metronome->SetTempo(tempo);
		RestartMetronome();

		return;
	}

	void Module::RestartMetronome()
	{

		if(isMetronomeEnabled)
		{
			EnableMetronome(false);
			EnableMetronome(true);
		}

		return;
	}


	// PRIVATE METHODS

	void Module::LoadKits()
	{

		// Clear kits list
		kits.clear();

		// Get all kits locations
		std::vector<std::string> kitsPaths = kitManager.GetKitsLocations();

		std::transform(kitsPaths.cbegin(), kitsPaths.cend(), std::back_inserter(kits), [this](std::string const& kitPath)
		{
			KitParameters kitParams;
			KitManager::LoadKit(kitPath, kitParams);

			return Kit(kitParams, this->triggers, this->soundBank);
		});

		return;
	}

	void Module::LoadTriggers()
	{

		// Update sensors configuration
		TriggerManager::LoadSensorsConfig(this->directory, sensorsConfig);

		// Load triggers
		std::vector<TriggerParameters> triggersParameters;
		TriggerManager::LoadTriggersConfig(this->directory, sensorsConfig, triggersParameters);

		// Create Triggers
		this->CreateTriggers(triggersParameters);

		return;
	}


	void Module::Run()
	{

		if(isMetronomeEnabled)
		{
			mixer->PlaySound(metronomeSoundId, 1.0f);
		}

		while(isPlay.load())
		{

			// Refresh triggers
			std::for_each(triggers.begin(), triggers.end(), [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });


			// Check instruments triggers and send sounds to mixer if necessary
			const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();
			for(const InstrumentPtr& instrumentPtr : instruments)
			{

				bool isTriggerEvent = instrumentPtr->IsTriggerEvent();

				if(isTriggerEvent)
				{
					int soundId = 0;
					float volume = 1.0f;
					instrumentPtr->GetSoundProps(soundId, volume);
					mixer->PlaySound(soundId, volume);
				}
			}
		}

		return;
	}


	void Module::CreateTriggers(const std::vector<TriggerParameters>& triggersParameters)
	{

		triggers.clear();

		for(const TriggerParameters& triggerParameters : triggersParameters)
		{

			TriggerPtr triggerPtr = nullptr;

			switch (triggerParameters.type)
			{

			case TriggerType::Discrete:   triggerPtr = std::make_shared<DiscreteTrigger>(triggerParameters);   break;
			case TriggerType::Continuous: triggerPtr = std::make_shared<ContinuousTrigger>(triggerParameters); break;

			default: throw -1; break;

			}

			triggers.push_back(triggerPtr);

		};


		return;
	}

}

