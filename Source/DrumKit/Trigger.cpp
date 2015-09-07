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


	Trigger::Trigger(Drum& drumParams, Sound::Mixer& mix)
	: drum(drumParams),
	  mixer(mix),
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


	void Trigger::Trig(short value)
	{

		// Data normalisation
		short v = std::abs(value - mean);

		velocity = v;

		// Get current time
		high_resolution_clock::time_point t = high_resolution_clock::now();
		unsigned long long dt = (unsigned long long) duration<double, std::micro>(t - t0).count();

		if(velocity > drum.threshold)
		{

			if(!trig)
			{
				 trigTime = dt;
				 trig = true;
			}

			if(maxVelocity < velocity && dt < trigTime + drum.scanTime)
			{
				maxVelocity = velocity;
			}

			if(dt > trigTime + drum.scanTime && !out)
			{
				out = true;

				float volume = drum.curve[maxVelocity];

				mixer.AddToMixer(drum.id, volume);
			}

		}

		if(trig && dt > trigTime + drum.maskTime)
		{
			trig = false;
			maxVelocity = 0;
			out = false;
		}

		return;
	}

}

