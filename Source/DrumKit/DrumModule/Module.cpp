/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"

namespace DrumKit
{

	Module::Module(std::string dir, std::shared_ptr<Mixer> mixer, std::shared_ptr<Metronome> metro)
	: directory(dir),
	  kitManager(dir + "Kits/"),  kitId(0),
	  isPlay(false),
	  mixer(mixer),
	  metronome(metro), metronomeSoundId(-1), isMetronomeEnabled(false)
	{

		this->soundProc = std::make_shared<SoundProcessor>(SoundProcessor());
		this->soundBank = std::make_shared<SoundBank>(SoundBank(dir));

		mixer->SetSoundBank(soundBank);


		// Load triggers
		std::vector<TriggerParameters> triggersParameters;
		TriggerManager::LoadTriggersConfig(this->directory, triggersParameters);

		// Create Triggers
		this->CreateTriggers(triggersParameters);

		// Load all drum kits
		LoadKits();

		// Select current kit
		SelectKit(kitId);

		return;
	}

	Module::~Module()
	{


		return;
	}

	std::string Module::GetInstrumentName(std::size_t id) const
	{

		std::string name(kits[kitId].GetInstrumentName(id));

		return name;
	}

	void Module::Start()
	{

		isPlay = true;
		playThread = std::thread(&Module::Run, this);

		return;
	}


	void Module::Stop()
	{

		isPlay = false;
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

	std::string Module::GetKitNameById(int id) const
	{

		return kits.at(id).GetName();
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

	void Module::EnableMetronome(bool enable)
	{

		if(enable)
		{
			//xxx Will change in the future
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


	void Module::Run()
	{

		if(isMetronomeEnabled)
		{
			mixer->PlaySound(metronomeSoundId, 1.0f);
		}

		while(isPlay)
		{

			// Refresh triggers
			std::for_each(triggers.begin(), triggers.end(), [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });


			// Check instruments triggers and send sounds to mixer if necessary
			const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();
			for(InstrumentPtr const& instrumentPtr : instruments)
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


	void Module::CreateTriggers(std::vector<TriggerParameters> const& triggersParameters)
	{

		for(TriggerParameters const& triggerParameters : triggersParameters)
		{

			TriggerPtr triggerPtr = nullptr;

			switch (triggerParameters.type)
			{

			case TriggerType::Discrete: triggerPtr = TriggerPtr(new DiscreteTrigger(triggerParameters)); break;

			default: throw -1; break;

			}

			triggers.push_back(triggerPtr);

		};


		return;
	}

}

