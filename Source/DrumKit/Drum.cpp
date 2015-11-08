/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

namespace DrumKit
{

	Drum::Drum(int id, int sensorId, IO::SensorType sensorType)
	: id(id),
	  sensorId(sensorId),
	  sensorType(sensorType),
	  scanTime(0),
	  threshold(0),
	  maskTime(0),
	  sensor(nullptr),
	  trigger(nullptr)
	{


		// Create sensor


		const std::string sensorLoc("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/out.raw");

		switch(sensorType)
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

	Drum::~Drum()
	{

		return;
	}


	void Drum::CreateTrigger()
	{

		TriggerParameters triggerParameters;

		triggerParameters.drumId = id;
		triggerParameters.scanTime = scanTime;
		triggerParameters.threshold = threshold;
		triggerParameters.maskTime = maskTime;
		triggerParameters.curve = curve;

		trigger = std::shared_ptr<Trigger>(new Trigger(triggerParameters));

		return;
	}

	bool Drum::Trig(float& volume)
	{

		short value = this->sensor->GetData(sensorId);

		bool isTrig = this->trigger->Trig(value, volume);

		return isTrig;
	}

	void Drum::SetDrumName(std::string drumName)
	{

		this->drumName = drumName;

		return;
	}

	void Drum::SetSoundFile(std::string soundFile)
	{

		this->soundFile = soundFile;

		return;
	}

	void Drum::SetCurve(std::vector<float> curve)
	{

		this->curve = curve;

		return;
	}

	void Drum::SetScanTime(unsigned int scanTime)
	{

		this->scanTime = scanTime;

		return;
	}

	void Drum::SetThreshold(short threshold)
	{

		this->threshold = threshold;

		return;
	}

	void Drum::SetMaskTime(int maskTime)
	{

		this->maskTime = maskTime;

		return;
	}

}


