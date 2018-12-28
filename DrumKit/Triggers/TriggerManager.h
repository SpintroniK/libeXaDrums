/*
 * TriggerManager.h
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_


#include "../../IO/SensorType.h"
#include "../../IO/SensorsConfig.h"

#include "TriggerParameters.h"


#include <string>
#include <vector>

namespace DrumKit
{

	class TriggerManager
	{

	public:

		static void LoadTriggersConfig(const std::string& moduleDir, const IO::SensorsConfig& sensorsConfig, std::vector<TriggerParameters>& trigsParams);
		static void SaveTriggersConfig(const std::string& moduleDir, const std::vector<TriggerParameters>& trigsParams);
		static std::vector<int> LoadTriggersIds(const std::string& moduleDir);
		static void LoadSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig);
		static void SaveSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig);

	private:

		TriggerManager() = delete;
		virtual ~TriggerManager() = delete;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H_ */
