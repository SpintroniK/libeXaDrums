/*
 * Instrument.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */


#include "Instrument.h"

namespace DrumKit
{

	Instrument::Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor)
	: parameters(parameters),
	  sensor(nullptr),
	  trigger(nullptr),
	  soundProcessor(soundProcessor),
	  soundIds()
	{

		// Create sensor
		//XXX Need to improve Hdd sensor
		const std::string sensorLoc("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/out.raw");

		switch(parameters.sensorType)
		{

		case IO::SensorType::Hdd:

			this->sensor = std::shared_ptr<IO::ISensor>(new IO::HddSensor(sensorLoc.c_str()));

			break;

		case IO::SensorType::Spi:

			this->sensor = std::shared_ptr<IO::ISensor>(new IO::SpiSensor());

			break;

		default:
			throw -1;
			break;

		}

		// Create instrument trigger
		this->CreateTrigger();

		return;
	}

	Instrument::~Instrument()
	{



		return;
	}

	/*void Instrument::SetSoundData(std::vector<short>& data, unsigned int duration)
	{

		this->soundData.clear();
		this->soundData.swap(data);
		this->soundDuration = duration;

		return;
	}*/

	// PRIVATE

	void Instrument::CreateTrigger()
	{

		TriggerParameters triggerParameters;

		triggerParameters.drumId = parameters.id;
		triggerParameters.scanTime = parameters.scanTime;
		triggerParameters.threshold = parameters.threshold;
		triggerParameters.maskTime = parameters.maskTime;
		//triggerParameters.curve = curve;


		switch(parameters.instrumentType)
		{

		case InstrumentType::Drum:
			trigger = std::shared_ptr<Trigger>(new DrumTrigger(triggerParameters));
			break;

		default:
			throw -1;
			break;

		}

		return;
	}




}

