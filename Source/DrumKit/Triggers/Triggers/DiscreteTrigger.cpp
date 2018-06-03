/*
 * Conditioner.cpp
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#include "DiscreteTrigger.h"

#include <chrono>

#include <cmath>


using namespace std::chrono;

namespace DrumKit
{


	DiscreteTrigger::DiscreteTrigger(const TriggerParameters& triggerParams) : Trigger(triggerParams)
	{

		return;
	}

	void DiscreteTrigger::Refresh()
	{


		//std::lock_guard<std::mutex> lock(triggerMutex);

		// Reset state value
		state.value = 0.0f;
		state.isTrig = false;

		// Read sensor date
		short value = this->GetSensorData();


		// Remove DC offset (high pass filter: y[n] = x[n] - x[n-1] + R * y[n-1])
		filteredValue = value  - prevValue + 0.99 * prevFilteredValue;

		// Update values
		prevValue = value;
		prevFilteredValue = filteredValue;

		velocity = std::abs(filteredValue);


		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		int64_t dt = static_cast<int64_t>(duration<double, std::micro>(t - t0).count());

		if(velocity > this->triggerParameters.threshold)
		{

			if(!trig)
			{
				 trigTime = dt;
				 trig = true;
			}

			if(maxVelocity < velocity && dt < trigTime + this->triggerParameters.scanTime)
			{
				maxVelocity = velocity;
			}

			if(dt > trigTime + this->triggerParameters.scanTime && !out)
			{
				out = true;

				// Update trigger state
				state.value = maxVelocity/numSamples;
				state.trigTime = static_cast<int64_t>(time_point_cast<microseconds>(t).time_since_epoch().count());
				state.isTrig = true;
			}

		}

		if(trig && dt > trigTime + this->triggerParameters.maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		return;
	}

}

