/*
 * Config_api.h
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_API_H_
#define SOURCE_API_CONFIG_API_H_

#include "../IO/SensorsConfig.h"

#include <vector>
#include <string>

namespace DrumKit { class Module; }

namespace eXaDrumsApi
{

	class eXaDrums;

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
		void SetSensorsType(const std::string& type);

		// Accessors
		std::vector<std::string> GetSensorsTypes();
		std::string GetSensorsType();
		int GetSensorsSamplingRate() const { return sensorsConfig.samplingRate; }
		int GetSensorsResolution() const { return sensorsConfig.resolution; }

	private:


		const char* GetSensorsType_();
		void GetSensorsTypes_(const char** types, unsigned int& size);


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

#endif /* SOURCE_API_CONFIG_API_H_ */
