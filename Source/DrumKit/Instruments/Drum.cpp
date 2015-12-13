/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

namespace DrumKit
{

	Drum::Drum(InstrumentParameters parameters) : Instrument(parameters)
	{



		return;
	}

	Drum::~Drum()
	{

		return;
	}

	bool Drum::Trig(float& strength)
	{

		short value = this->sensor->GetData(parameters.sensorId);

		bool isTrig = this->trigger->Trig(value, strength);

		return isTrig;
	}

}


