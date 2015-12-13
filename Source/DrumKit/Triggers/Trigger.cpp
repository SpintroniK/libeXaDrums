/*
 * Trigger.cpp
 *
 *  Created on: 13 Dec 2015
 *      Author: jeremy
 */


#include "Trigger.h"

namespace DrumKit
{

	Trigger::Trigger(TriggerParameters triggerParams)
	: triggerParameters(triggerParams),
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



}
