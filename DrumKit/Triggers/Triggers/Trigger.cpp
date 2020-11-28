/*
 * Trigger.cpp
 *
 *  Created on: 13 Dec 2015
 *      Author: jeremy
 */


#include "Trigger.h"

#include "../../../IO/HddSensor.h"
#include "../../../IO/SpiSensor.h"
#include "../../../IO/VirtualSensor.h"

#include <string>
#include <algorithm>
#include <mutex>

#include <cmath>

using namespace std::chrono;
using namespace Util;

namespace DrumKit
{

	Trigger::Trigger(TriggerParameters triggerParams)
	: trig(false),
	  out(false),
	  trigTime(0),
	  velocity(0),
	  maxVelocity(0),
	  state(),
	  triggerParameters(triggerParams)
	{

		t0 = high_resolution_clock::now();

		numSamples = static_cast<size_t>(std::pow(2.0f, triggerParams.sensorConfig.resolution) / 2.0f);
		//mean = numSamples;

		prevValue = 0;
		filteredValue = 0;
		prevFilteredValue = 0;

		// Default state values
		state.isTrig = false;
		state.sensorId = triggerParams.sensorId;
		state.value = 0.0f;

		const std::string dataFolder = triggerParams.sensorConfig.hddDataFolder;

		switch(triggerParams.sensorConfig.sensorType)
		{

			case IO::SensorType::Hdd: this->sensor = std::make_unique<IO::HddSensor>(dataFolder); break;
			case IO::SensorType::Spi: this->sensor = std::make_unique<IO::SpiSensor>(); break;
			case IO::SensorType::Virtual: this->sensor = std::make_unique<IO::VirtualSensor>(); break;

			default: throw -1; break;

		}

		// Generate curves
		const auto curves_types = Enums::GetEnumVector<CurveType>();
		curves.resize(curves_types.size());
		std::transform(curves_types.cbegin(), curves_types.cend(), curves.begin(), [&](const auto& t) { return Curves::MakeCurve<float>(t, numSamples);});


		return;
	}

	short Trigger::GetSensorData() const
	{
		return sensor->GetData(triggerParameters.sensorId);
	}

	void Trigger::SetParameters(const TriggerParameters& params)
	{
		std::lock_guard<SpinLock> lock(spin);

		const auto sensorConfig = triggerParameters.sensorConfig;
		triggerParameters = params;
		triggerParameters.sensorConfig = sensorConfig;
	}


	TriggerParameters Trigger::GetParameters() const
	{
		std::lock_guard<SpinLock> lock(spin);

		return triggerParameters;
	}

}
