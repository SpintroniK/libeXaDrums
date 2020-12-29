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


		// Reset state value
		state.value = 0.0f;
		state.isTrig = false;

		const auto parameters = this->GetParameters();

		// Read sensor date
		double value = parameters.gain * this->GetSensorData();

		// Remove DC offset (high pass filter: y[n] = x[n] - x[n-1] + R * y[n-1])
		filteredValue = value - prevValue + 0.99 * prevFilteredValue;

		// Update values
		prevValue = value;
		prevFilteredValue = filteredValue;

		velocity = std::abs(filteredValue);

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		int64_t dt = static_cast<int64_t>(duration<double, std::micro>(t - t0).count());

		if(velocity > parameters.threshold)
		{

			if(!trig)
			{
				 trigTime = dt;
				 trig = true;
			}

			if(maxVelocity < velocity && dt < trigTime + parameters.scanTime)
			{
				maxVelocity = velocity;
			}

			if(sensor->IsDigital() || (dt > trigTime + parameters.scanTime && !out))
			{
				out = true;

				// Update trigger state
				state.value = Curves::Apply(this->curves[static_cast<size_t>(parameters.response)], maxVelocity);
				state.trigTime = static_cast<int64_t>(time_point_cast<microseconds>(t).time_since_epoch().count());
				state.isTrig = true;

				lastTrigValue = state.value;
			}

		}

		if(trig && dt > trigTime + parameters.maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		return;
	}

}

