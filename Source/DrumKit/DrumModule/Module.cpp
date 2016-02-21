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
	  soundProc(soundProc)
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

		while(!playThread.joinable());

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

		// Load drum kit parameters
		KitParameters::LoadKit(file, this->kitParameters);


		std::function<void(InstrumentParameters)> fInst = [this](InstrumentParameters instrumentParameters)
		{



			// Add sound data to soundData vector
			//Sound::SoundBank::LoadSound(soundLocation, soundData, soundDuration);

			//XXX Force sensor type to the one defined by the module (temporary)
			instrumentParameters.sensorType = this->sensorType;

			//XXX Force curve to linear (temporary)
			instrumentParameters.curveType = Sound::CurveType::linear;

			std::shared_ptr<Instrument> instrument = nullptr;

			//XXX Create instrument for drum module (Drum only for now)
			switch(instrumentParameters.instrumentType)
			{

			case InstrumentType::Drum:
				instrument = std::shared_ptr<Instrument>(new Drum(instrumentParameters));
				break;

			default:
				throw -1;
				break;

			}

			//FIXME Set sounds for instrument and SoundProcessor

			// Set sound data for this instrument
			//instrument->SetSoundData(soundData, soundDuration);

			// Create trigger for the instrument
			instrument->CreateTrigger();

			//this->soundProc->SetInstrumentSounds(instrument->GetSoundData(), instrument->GetSoundDuration());

			// Add instrument to drum module
			instruments.push_back(instrument);

		};

		std::for_each(this->kitParameters.instrumentParameters.begin(),
				this->kitParameters.instrumentParameters.end(), fInst);



		return;
	}


	/// PRIVATE


	void Module::Run()
	{

		std::function<void(std::shared_ptr<Instrument>)> f = [this] (std::shared_ptr<Instrument> instrument)
		{

			float strength = 0;
			bool isTrig = instrument->Trig(strength);

			if(isTrig)
			{
				//TODO convert strength to volume (SoundProcessor)
				this->soundProc->AddSound(instrument->GetId(), strength);
			}

		};

		while(isPlay)
		{
			std::for_each(instruments.begin(), instruments.end(), f);
		}

		return;
	}



}

