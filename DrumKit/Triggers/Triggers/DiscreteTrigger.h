/*
 * Conditioner.h
 *
 *  Created on: 4 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_

#include "../../../IO/SensorFactory.h"
#include "../TriggerParameters.h"
#include "Trigger.h"


namespace DrumKit
{

	class DiscreteTrigger : public Trigger
	{

	public:

		explicit DiscreteTrigger(const TriggerParameters& triggerParams, const IO::SensorFactory& sensorFactory);
		~DiscreteTrigger() = default;

		virtual void Refresh() final;
		//virtual bool Trig(short value, float& strength);
		//bool GetState() const { return trig; }


	private:

		//mutable std::mutex triggerMutex;

	};



}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_TRIGGER_H_ */
