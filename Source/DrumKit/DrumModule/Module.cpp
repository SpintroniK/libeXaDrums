/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"

namespace DrumKit
{

	Module::Module(std::string dir,	IO::SensorType sensorType, std::shared_ptr<Sound::Mixer> mixer)
	: soundBank(dir),
	  kitManager(dir + "Kits/"),
	  sensorType(sensorType),
	  directory(dir),
	  isPlay(false),
	  mixer(mixer),
	  triggers()
	{

		this->soundProc = std::shared_ptr<Sound::SoundProcessor>(new Sound::SoundProcessor());

		return;
	}

	Module::~Module()
	{


		return;
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
		mixer->Dump();
		return;
	}

	void Module::GetDirectory(std::string& dir) const
	{

		dir = this->directory;

		return;
	}

	void Module::LoadKit(std::string file)
	{


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

		// Load drum kit parameters
		this->kitManager.LoadKit(file, this->kitParameters);

		// Create Instruments
		this->CreateInstruments();


		return;
	}


	/// PRIVATE


	void Module::Run()
	{

		while(isPlay)
		{

			// Refresh triggers
			std::for_each(triggers.begin(), triggers.end(), [](TriggerPtr triggerPtr)
			{
				triggerPtr->Refresh();
			});


			std::for_each(instruments.cbegin(), instruments.cend(), [this](InstrumentPtr instrumentPtr)
			{

				bool isTriggerEvent = instrumentPtr->isTriggerEvent();


				if(isTriggerEvent)
				{
					Sound::SoundPtr sound = instrumentPtr->GetSound();
					mixer->SetSound(instrumentPtr->GetId(), sound);
				}

			});

		}

		return;
	}


	void Module::CreateTriggers()
	{

		std::function<void(TriggerParameters)> fTrig = [this](TriggerParameters triggerParameters)
		{

			TriggerPtr triggerPtr = nullptr;

			switch (triggerParameters.type)
			{
			case TriggerType::Discrete:
				triggerPtr = TriggerPtr(new DiscreteTrigger(triggerParameters));
				break;

			default:
					throw -1;
				break;
			}

			triggers.push_back(triggerPtr);

		};

		std::for_each(this->triggersParameters.begin(), this->triggersParameters.end(), fTrig);

		return;
	}

	void Module::CreateInstruments()
	{


		std::function<void(InstrumentParameters)> fInst = [this](InstrumentParameters instrumentParameters)
		{


			InstrumentPtr instrumentPtr = nullptr;

			switch(instrumentParameters.instrumentType)
			{

			case InstrumentType::TestDrum:
				instrumentPtr = InstrumentPtr(new TestDrum(instrumentParameters));
				break;

			default:
				throw -1;
				break;

			}

			// Create instrument's triggers
			instrumentPtr->SetTriggers(this->triggers);

			// Set instrument sounds
			std::for_each(instrumentParameters.soundsInfo.cbegin(), instrumentParameters.soundsInfo.cend(),
			[this, &instrumentPtr] (InstrumentSoundInfo const& soundInfo)
			{
				instrumentPtr->SetSound(soundInfo, this->soundBank, this->soundProc);
			});

			// Add instrument to drum module
			instruments.push_back(instrumentPtr);

		};

		std::for_each(this->kitParameters.instrumentParameters.cbegin(),
				this->kitParameters.instrumentParameters.cend(), fInst);

		return;
	}


}

