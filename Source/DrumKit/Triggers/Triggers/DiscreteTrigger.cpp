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


		// Data normalisation
		short v = std::abs(value - mean);

		velocity = v;

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		long long dt = (long long) duration<double, std::micro>(t - t0).count();

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
				state.trigTime = (long long) time_point_cast<microseconds>(t).time_since_epoch().count();
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

