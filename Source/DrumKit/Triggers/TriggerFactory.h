/*
 * TriggerFactory.h
 *
 *  Created on: 18 Jun 2017
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_

#include "Triggers/DiscreteTrigger.h"
#include "Triggers/ContinuousTrigger.h"

namespace DrumKit
{

	class TriggerFactory
	{

	public:

		static TriggerPtr CreateTrigger(const TriggerParameters& triggerParameters)
		{

			switch (triggerParameters.type)
			{

			case TriggerType::Discrete:   return std::make_shared<DiscreteTrigger>(triggerParameters);
			case TriggerType::Continuous: return std::make_shared<ContinuousTrigger>(triggerParameters);

			default: throw -1; break;

			}
		}

	private:

		TriggerFactory() = delete;
		~TriggerFactory() = delete;

	};


}  // namespace DrumKit



#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_ */
