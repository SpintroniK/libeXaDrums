/*
 * TriggerManager.h
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_


#include "../../IO/SensorType.h"

#include "TriggerParameters.h"


#include <string>
#include <vector>

namespace DrumKit
{

	class TriggerManager
	{

	public:

		TriggerManager();
		virtual ~TriggerManager();

		static void LoadTriggersConfig(const std::string& moduleDir, std::vector<TriggerParameters>& trigsParams);

	private:

		static void LoadSensorsConfig(const std::string& moduleDir, IO::SensorType& sensorType);

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_ */
