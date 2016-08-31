/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"

namespace DrumKit
{

	Module::Module(std::string dir, std::shared_ptr<Sound::Mixer> mixer, std::shared_ptr<Metronome> metro)
	: kitId(0),
	  kitManager(dir + "Kits/"),
	  directory(dir),
	  isPlay(false),
	  mixer(mixer),
	  metronome(metro),
	  triggers()
	{

		this->soundProc = std::make_shared<Sound::SoundProcessor>(Sound::SoundProcessor());
		this->soundBank = std::make_shared<Sound::SoundBank>(Sound::SoundBank(dir));

		mixer->SetSoundBank(soundBank);
		LoadKits();


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
		soundBank->Clear();

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

		kitId = id;

		// Prepare instruments vector to be populated
		this->instruments.clear();

		// Prepare trigger parameters vector
		this->triggersParameters.clear();

		// Clear current triggers
		this->triggers.clear();

		// Read triggers configurations
		this->kitManager.LoadTriggersConfig(this->directory, triggersParameters);

		// Create Triggers
		this->CreateTriggers();

		//Load drum kit parameters
		this->kitParameters = kits[id].parameters;

		// Create Instruments
		this->CreateInstruments();


		return;
	}

	std::string Module::GetKitNameById(int id) const
	{

		return kits.at(id).GetName();
	}

	void Module::SetInstrumentVolume(int id, float volume)
	{

		// Normalize volume
		volume /= 100;

		// Set instrument's volume
		this->instruments[id]->SetVolume(volume);

		return;
	}

	/// PRIVATE

	void Module::LoadKits()
	{

		// Clear kits list
		kits.clear();

		// Get all kits locations
		std::vector<std::string> kitsPaths = kitManager.GetKitsLocations();

		std::transform(kitsPaths.cbegin(), kitsPaths.cend(), std::back_inserter(kits), [this](std::string const& kitPath)
		{
			KitParameters kitParams;
			kitManager.LoadKit(kitPath, kitParams);

			return Kit(kitParams);
		});

		return;
	}


	void Module::Run()
	{

		while(isPlay)
		{

			// Refresh triggers
			std::for_each(triggers.begin(), triggers.end(), [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });


			// Check instruments triggers and send sounds to mixer if necessary
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


	void Module::CreateTriggers()
	{

		for(TriggerParameters const& triggerParameters : this->triggersParameters)
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

	void Module::CreateInstruments()
	{


		for(InstrumentParameters const& instrumentParameters : this->kitParameters.instrumentParameters)
		{

			// Create instrument
			InstrumentPtr instrumentPtr = nullptr;
			switch(instrumentParameters.instrumentType)
			{

			case InstrumentType::TestDrum: instrumentPtr = InstrumentPtr(new TestDrum(instrumentParameters, soundBank)); break;

			default: throw -1; break;

			}

			// Create instrument's triggers
			instrumentPtr->SetTriggers(this->triggers);

			// Set instrument sounds
			for(InstrumentSoundInfo const& soundInfo : instrumentParameters.soundsInfo)
			{
				instrumentPtr->SetSound(soundInfo, this->soundProc);
			}

			// Add instrument to drum module
			instruments.push_back(instrumentPtr);

		};


		return;
	}


}

