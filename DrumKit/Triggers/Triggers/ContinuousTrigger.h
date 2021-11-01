/*
 * ContinuousTrigger.h
 *
 *  Created on: 28 Oct 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_

#include "../../../IO/SensorFactory.h"
#include "../TriggerParameters.h"
#include "Trigger.h"

#include <memory>

namespace DrumKit
{

	class ContinuousTrigger : public Trigger
	{

	public:

		ContinuousTrigger(const TriggerParameters& triggerParams, const IO::SensorFactory& sensorFactory);
		~ContinuousTrigger() = default;

		virtual void Refresh() final;

	private:

	};


} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_ */
