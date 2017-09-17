/*
 * ContinuousTrigger.h
 *
 *  Created on: 28 Oct 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_

#include "Trigger.h"
#include "../TriggerParameters.h"

namespace DrumKit
{

	class ContinuousTrigger : public Trigger
	{

	public:

		explicit ContinuousTrigger(const TriggerParameters& triggerParams);
		~ContinuousTrigger() = default;

		virtual void Refresh() final;

	private:

	};


} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERS_CONTINUOUSTRIGGER_H_ */
