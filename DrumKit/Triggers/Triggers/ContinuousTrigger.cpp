/*
 * ContinuousTrigger.cpp
 *
 *  Created on: 28 Oct 2016
 *      Author: jeremy
 */

#include "ContinuousTrigger.h"

namespace DrumKit
{

	ContinuousTrigger::ContinuousTrigger(const TriggerParameters& triggerParams) : Trigger(triggerParams)
	{

		return;
	}


	void ContinuousTrigger::Refresh()
	{

		// Save previous value
		//float previousValue = state.value;

		// Reset state value
		state.value = 0.0f;
		state.isTrig = false;

		// Read sensor date
		short value = this->GetSensorData();

		state.value = value / numSamples / 2.0f;
		lastTrigValue = state.value;

		return;
	}


} /* namespace DrumKit */
