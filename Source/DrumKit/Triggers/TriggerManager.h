/*
 * TriggerManager.h
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_

#include "../../Util/Enums.h"

#include "Curves/CurveType.h"
#include "TriggerParameters.h"
#include "TriggerLocation.h"

#include <tinyxml2.h>

#include <string>
#include <vector>

namespace DrumKit
{

	class TriggerManager
	{

	public:

		TriggerManager();
		virtual ~TriggerManager();

		static void LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams);

	private:

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_ */
