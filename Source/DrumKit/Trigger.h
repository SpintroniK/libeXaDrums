/*
 * Conditioner.h
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_

#include "Kit.h"

#include "../Sound/Mixer.h"

#include <chrono>
#include <iostream>
#include <cmath>

using namespace std::chrono;

namespace DrumKit
{

	class Trigger
	{

	public:

		Trigger(Drum& drumParams, Sound::Mixer& mix);
		virtual ~Trigger();

		void Trig(short value);
		bool GetState() const { return trig; }

	private:

		Drum& drum;
		Sound::Mixer& mixer;


		high_resolution_clock::time_point t0;

		short mean;

		bool trig;
		bool out;

		unsigned long long trigTime;

		short velocity;
		short maxVelocity;

	};



}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_ */
