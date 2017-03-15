/*
 * Config_api.h
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_CONFIG_API_H_
#define SOURCE_API_CONFIG_CONFIG_API_H_

#include "../../IO/SensorsConfig.h"

#include <vector>
#include <string>

namespace DrumKit { class Module; }
namespace eXaDrumsApi{ class eXaDrums; struct TriggerParameters; }

namespace eXaDrumsApi
{

	class Config
	{

	public:

		Config(eXaDrums& drums);
		virtual ~Config() = default;

		void RefreshSensorsConfig();
		void SaveSensorsConfig();


		// Mutators
		void SetSensorsSamplingRate(int sRate) { sensorsConfig.samplingRate = sRate; }
		void SetSensorsResolution(int res) { sensorsConfig.resolution = res; }
		void SetSensorsType(const std::string type);
		void SetSensorsDataFolder(const std::string folder);

		// Accessors
		std::vector<std::string> GetSensorsTypes();
		std::vector<TriggerParameters> GetTriggersParameters() const;
		std::string GetSensorsType();
		std::string GetSensorsDataFolder() const;
		int GetSensorsSamplingRate() const { return sensorsConfig.samplingRate; }
		int GetSensorsResolution() const { return sensorsConfig.resolution; }

	private:

		void SetSensorsType_(const char* type);
		void SetSensorsDataFolder_(const char* folder);

		const char* GetSensorsType_();
		const char* GetSensorsDataFolder_() const;
		void GetSensorsTypes_(const char** types, unsigned int& size);
		void GetTriggersParameters_(TriggerParameters* const triggers, unsigned int& size) const;

		eXaDrums& drumKit;
		DrumKit::Module& module;

		// Sensors config
		IO::SensorsConfig sensorsConfig;

		// Local copies of items
		std::string sensorType;

		// Local copies of enums
		std::vector<std::string> sensorsTypes;

	};

}

#include "Config_api.hpp"

#endif /* SOURCE_API_CONFIG_CONFIG_API_H_ */
