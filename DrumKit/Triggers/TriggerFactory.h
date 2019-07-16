/*
 * TriggerFactory.h
 *
 *  Created on: 18 Jun 2017
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_

#include "../../Util/ErrorHandling.h"
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

			default: Util::Exception("Unknown trigger type.", Util::error_type_error); return TriggerPtr(nullptr);

			}
		}

	private:

		TriggerFactory() = delete;
		~TriggerFactory() = delete;

	};


}  // namespace DrumKit



#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERFACTORY_H_ */
