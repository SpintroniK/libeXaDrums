/*
 * Conditioner.cpp
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#include "DrumTrigger.h"

using namespace std::chrono;

namespace DrumKit
{


	DrumTrigger::DrumTrigger(TriggerParameters triggerParams) : Trigger(triggerParams)
	{

		return;
	}

	DrumTrigger::~DrumTrigger()
	{


		return;
	}


	void DrumTrigger::Refresh()
	{

		// Reset state value
		state.strength = 0.0f;
		state.isTrig = false;

		// Read sensor date
		short value = this->GetSensorData();


		// Data normalisation
		short v = std::abs(value - mean);

		velocity = v;

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		unsigned long long dt = (unsigned long long) duration<double, std::micro>(t - t0).count();

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
				state.strength = maxVelocity/numSamples;
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

