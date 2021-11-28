/*
 * TriggerManager.h
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H
#define LIBEXADRUMS_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H

#include "../../IO/SensorsConfig.h"
#include "../../IO/SpiDevices/SpiDevParameters.h"

#include "TriggerParameters.h"

#include <string>
#include <vector>
#include <memory>

namespace IO { class SpiDev; }

namespace DrumKit
{

	class TriggerManager
	{

	public:

		TriggerManager() = delete;

		static void LoadTriggersConfig(const std::string& moduleDir, const IO::SensorsConfig& sensorsConfig, std::vector<TriggerParameters>& trigsParams);
		static void SaveTriggersConfig(const std::string& moduleDir, const std::vector<TriggerParameters>& trigsParams);
		static std::vector<int> LoadTriggersIds(const std::string& moduleDir);
		static void LoadSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig);
		static void SaveSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig);
		static void LoadSpiDevConfig(const std::string& moduleDir, std::vector<std::unique_ptr<IO::SpiDev>>& spidev);
		static void SaveSpiDevConfig(const std::string& moduleDir, const std::vector<std::unique_ptr<IO::SpiDev>>& spidev);
		static void LoadSpiDevParams(const std::string& moduleDir, std::vector<IO::SpiDevParameters>& spidevParams);
		static void SaveSpiDevParams(const std::string& moduleDir, const std::vector<IO::SpiDevParameters>& spidevParams);

	private:

	};

} /* namespace DrumKit */

#endif /* LIBEXADRUMS_DRUMKIT_TRIGGERS_TRIGGERMANAGER_H */
