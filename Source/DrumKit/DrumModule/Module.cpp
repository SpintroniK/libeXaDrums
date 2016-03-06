/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"


namespace DrumKit
{

	Module::Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::SoundProcessor> const& soundProc)
	: sensorType(sensorType),
	  directory(dir),
	  isPlay(false),
	  soundProc(soundProc),
	  triggers()
	{

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

		// Read triggers configurations
		KitParameters::LoadTriggersConfig(this->directory, triggersParameters);

		// Load drum kit parameters
		KitParameters::LoadKit(file, this->kitParameters);

		// Create Triggers
		this->CreateTriggers();

		// Populate trigStates
		std::transform(triggers.begin(), triggers.end(), std::back_inserter(trigStates),
						[](std::shared_ptr<Trigger> trigger) { return trigger->GetTriggerState(); });

		// Create Instruments
		this->CreateInstruments();


		return;
	}


	/// PRIVATE


	void Module::Run()
	{

		while(isPlay)
		{

			// Refresh triggers states
			std::for_each(triggers.begin(), triggers.end(), [](std::shared_ptr<Trigger> trigger) { trigger->Refresh(); });

		}

		return;
	}


	void Module::CreateTriggers()
	{

		std::function<void(TriggerParameters)> fTrig = [this](TriggerParameters triggerParameters)
		{

			std::shared_ptr<Trigger> trigger = nullptr;

			switch (triggerParameters.type)
			{
			case TriggerType::Drum:
				trigger = std::shared_ptr<Trigger>(new DrumTrigger(triggerParameters));
				break;

			default:
					throw -1;
				break;
			}

			this->triggers.push_back(trigger);

		};

		std::for_each(this->triggersParameters.begin(), this->triggersParameters.end(), fTrig);

		return;
	}

	void Module::CreateInstruments()
	{


		std::function<void(InstrumentParameters)> fInst = [this](InstrumentParameters instrumentParameters)
		{


			std::shared_ptr<Instrument> instrument = nullptr;

			//XXX Create instrument for drum module (Drum only for now)
			switch(instrumentParameters.instrumentType)
			{

			case InstrumentType::Drum:
				instrument = std::shared_ptr<Instrument>(new Drum(instrumentParameters, soundProc));
				break;

			default:
				throw -1;
				break;

			}


			// Add instrument to drum module
			instruments.push_back(instrument);

		};

		std::for_each(this->kitParameters.instrumentParameters.begin(),
				this->kitParameters.instrumentParameters.end(), fInst);

		return;
	}


}

