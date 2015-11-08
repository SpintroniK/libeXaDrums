/*
 * Conditioner.cpp
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#include "Trigger.h"

using namespace std::chrono;

namespace DrumKit
{


	Trigger::Trigger(int drumId, unsigned int scanTime, short threshold, int maskTime, std::vector<float> curve)
	: drumId(drumId),
	  scanTime(scanTime),
	  threshold(threshold),
	  maskTime(maskTime),
	  curve(curve),
	  mean(2046),
	  trig(false),
	  out(false),
	  trigTime(0),
	  velocity(0),
	  maxVelocity(0)
	{

		t0 = high_resolution_clock::now();

		return;
	}

	Trigger::~Trigger()
	{


		return;
	}


	bool Trigger::Trig(short value, float& volume)
	{

		// Data normalisation
		short v = std::abs(value - mean);

		velocity = v;

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		unsigned long long dt = (unsigned long long) duration<double, std::micro>(t - t0).count();

		if(velocity > this->threshold)
		{

			if(!trig)
			{
				 trigTime = dt;
				 trig = true;
			}

			if(maxVelocity < velocity && dt < trigTime + this->scanTime)
			{
				maxVelocity = velocity;
			}

			if(dt > trigTime + this->scanTime && !out)
			{
				out = true;

				volume = this->curve[maxVelocity];

				//mixer->AddToMixer(this->drumId, volume);
				return true;
			}

		}

		if(trig && dt > trigTime + this->maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		volume = 0;

		return false;
	}

}

