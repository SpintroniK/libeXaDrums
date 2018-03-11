/*
 * ITrigger.h
 *
 *  Created on: 9 Dec 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_


#include "../../../IO/ISensor.h"

#include "../TriggerParameters.h"
#include "../TriggerState.h"

#include <chrono>
#include <memory>


namespace DrumKit
{

	class Trigger
	{

	public:


		explicit Trigger(TriggerParameters trigParams);

		//virtual bool Trig(short value, float& strength) = 0;
		virtual void Refresh() = 0;

		virtual int GetId() const { return this->triggerParameters.sensorId; };
		virtual TriggerType GetType() const { return this->triggerParameters.type; }
		virtual TriggerState const& GetTriggerState() const { return state; }


	protected:

		virtual ~Trigger() = default;

		virtual short GetSensorData() const { return sensor->GetData(triggerParameters.sensorId); }

		TriggerParameters triggerParameters;

		std::chrono::high_resolution_clock::time_point t0;

		float numSamples;

		short prevValue;
		short filteredValue;
		short prevFilteredValue;

		bool trig;
		bool out;

		int64_t trigTime;

		short velocity;
		short maxVelocity;

		TriggerState state;


	private:

		std::unique_ptr<IO::ISensor> sensor;


	};


	typedef std::shared_ptr<Trigger> TriggerPtr;


}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_ */
