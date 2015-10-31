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


	Trigger::Trigger(int drumId, unsigned int scanTime, short threshold, int maskTime, std::vector<float> curve, std::shared_ptr<Sound::Mixer> const& mix)
	: mixer(mix),
	  mean(2046),
	  trig(false),
	  out(false),
	  trigTime(0),
	  velocity(0),
	  maxVelocity(0),
	  drumId(drumId),
	  scanTime(scanTime),
	  threshold(threshold),
	  maskTime(maskTime),
	  curve(curve)
	{

		t0 = high_resolution_clock::now();

		return;
	}

	Trigger::~Trigger()
	{


		return;
	}


	void Trigger::Trig(short value)
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

				float volume = this->curve[maxVelocity];

				mixer->AddToMixer(this->drumId, volume);
			}

		}

		if(trig && dt > trigTime + this->maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		return;
	}

}

