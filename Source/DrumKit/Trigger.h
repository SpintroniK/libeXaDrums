/*
 * Conditioner.h
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_

#include "../Sound/Mixer.h"

#include "Kit.h"

#include <chrono>
#include <iostream>
#include <vector>
#include <memory>

#include <cmath>

using namespace std::chrono;

namespace DrumKit
{

	class Trigger
	{

	public:

		Trigger(int drumId, unsigned int scanTime, short threshold, int maskTime, std::vector<float> curve, std::shared_ptr<Sound::Mixer> const& mix);
		virtual ~Trigger();

		void Trig(short value);
		bool GetState() const { return trig; }

	private:

		std::shared_ptr<Sound::Mixer> mixer;

		high_resolution_clock::time_point t0;

		// Drum trigger parameters
		int drumId;
		unsigned int scanTime;
		short threshold;
		int maskTime;
		std::vector<float> curve;


		short mean;

		bool trig;
		bool out;

		unsigned long long trigTime;

		short velocity;
		short maxVelocity;

	};



}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_ */
