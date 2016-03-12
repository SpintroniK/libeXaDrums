/*
 * ITrigger.h
 *
 *  Created on: 9 Dec 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_


#include "../../IO/ISensor.h"
#include "../../IO/HddSensor.h"
#include "../../IO/SpiSensor.h"

#include "TriggerParameters.h"
#include "TriggerState.h"

#include <chrono>
#include <string>
#include <memory>


using namespace std::chrono;

namespace DrumKit
{

	class Trigger
	{

	public:


		Trigger(TriggerParameters trigParams);
		virtual ~Trigger() {};

		//virtual bool Trig(short value, float& strength) = 0;
		virtual void Refresh() = 0;

		virtual int GetId() const { return this->triggerParameters.sensorId; };
		virtual TriggerType GetType() const { return this->triggerParameters.type; }
		virtual TriggerState const& GetTriggerState() const { return state; }


	protected:

		virtual short GetSensorData() const { return sensor->GetData(triggerParameters.sensorId); }

		TriggerParameters triggerParameters;

		high_resolution_clock::time_point t0;

		static constexpr float numSamples = 2048.0f;

		short mean;

		bool trig;
		bool out;

		unsigned long long trigTime;

		short velocity;
		short maxVelocity;

		TriggerState state;


	private:

		std::unique_ptr<IO::ISensor> sensor;


	};


	typedef std::shared_ptr<Trigger> TriggerPtr;


}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGER_H_ */
