/*
 * ITrigger.h
 *
 *  Created on: 9 Dec 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_


#include "../Curves/Curves.h"
#include "../../../IO/ISensor.h"
#include "../../../Util/Threading.h"

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

		virtual void SetParameters(const TriggerParameters& params);
		virtual void SetSensorData(char channel, short data) { this->sensor->SetData(channel, data); }

		virtual int GetId() const { return this->triggerParameters.sensorId; };
		virtual TriggerType GetType() const { return this->triggerParameters.type; }
		virtual TriggerState const& GetTriggerState() const { return state; }
		virtual float GetLastTrigValue() const { return lastTrigValue; }
		virtual TriggerParameters GetParameters() const;


	protected:

		virtual ~Trigger() = default;

		virtual short GetSensorData() const;

		std::chrono::high_resolution_clock::time_point t0;

		size_t numSamples;

		float lastTrigValue = 0.f;
		double prevValue;
		double filteredValue{};
		double prevFilteredValue;

		bool trig;
		bool out;
		bool reset = false;

		int64_t trigTime;

		double velocity;
		double maxVelocity;

		TriggerState state;
		std::vector<curve_t<float>> curves;
		std::unique_ptr<IO::ISensor> sensor;

	private:

		mutable Util::SpinLock spin;
		TriggerParameters triggerParameters;

	};


	typedef std::shared_ptr<Trigger> TriggerPtr;


}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_TRIGGER_H_ */
