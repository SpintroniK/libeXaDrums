/*
 * Instrument.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */


#include "Instrument.h"

namespace DrumKit
{

	Instrument::Instrument(InstrumentParameters parameters) : parameters(parameters)
	{

		// Create sensor
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
			break;

		}


		return;
	}

	Instrument::~Instrument()
	{

		return;
	}

	void Instrument::CreateTrigger()
	{

		TriggerParameters triggerParameters;

		triggerParameters.drumId = parameters.id;
		triggerParameters.scanTime = parameters.scanTime;
		triggerParameters.threshold = parameters.threshold;
		triggerParameters.maskTime = parameters.maskTime;
		//triggerParameters.curve = curve;

		trigger = std::shared_ptr<Trigger>(new DrumTrigger(triggerParameters));

		return;
	}




}

