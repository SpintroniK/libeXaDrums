/*
 * Trigger.cpp
 *
 *  Created on: 13 Dec 2015
 *      Author: jeremy
 */


#include "Trigger.h"

#include "../../../IO/HddSensor.h"
#include "../../../IO/SpiSensor.h"

#include <string>


using namespace std::chrono;

namespace DrumKit
{

	Trigger::Trigger(TriggerParameters triggerParams)
	: triggerParameters(triggerParams),
	  mean(2046),
	  trig(false),
	  out(false),
	  trigTime(0),
	  velocity(0),
	  maxVelocity(0),
	  state()
	{

		t0 = high_resolution_clock::now();

		// Default state values
		state.isTrig = false;
		state.sensorId = triggerParams.sensorId;
		state.value = 0.0f;

		const std::string dataFolder("/home/jeremy/Desktop/Prog/eXaDrums/eXaDrums/");

		switch(triggerParams.sensorType)
		{

		case IO::SensorType::Hdd: this->sensor = std::unique_ptr<IO::ISensor>(new IO::HddSensor(dataFolder.c_str())); break;
		case IO::SensorType::Spi: this->sensor = std::unique_ptr<IO::ISensor>(new IO::SpiSensor()); break;

		default: throw -1; break;

		}


		return;
	}



}
