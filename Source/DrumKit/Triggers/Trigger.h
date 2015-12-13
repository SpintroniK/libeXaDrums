/*
 * ITrigger.h
 *
 *  Created on: 9 Dec 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_

#include "TriggerParameters.h"

#include <chrono>

using namespace std::chrono;

namespace DrumKit
{

	class Trigger
	{

	public:


		Trigger(TriggerParameters trigParams);

		virtual bool Trig(short value, float& strength) = 0;

		virtual ~Trigger() {};


	protected:

		TriggerParameters triggerParameters;

		high_resolution_clock::time_point t0;

		static constexpr float numSamples = 2048.0f;

		short mean;

		bool trig;
		bool out;

		unsigned long long trigTime;

		short velocity;
		short maxVelocity;


	private:



	};


}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_ */
