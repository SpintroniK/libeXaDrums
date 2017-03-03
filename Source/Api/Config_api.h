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

namespace eXaDrumsApi
{

	class eXaDrums;

	class Config
	{

	public:

		Config(eXaDrums& drums);
		virtual ~Config() = default;

		void RefreshSesorsConfig();

		// Accessors
		std::vector<std::string> GetSensorsTypes();
		int GetSensorsSamplingRate() const { return sensorsConfig.samplingRate; }
		int GetSensorsResolution() const { return sensorsConfig.resolution; }
		std::string GetSensorsType();

	private:


		const char* GetSensorsType_();
		void GetSensorsTypes_(const char** types, unsigned int& size);


		eXaDrums& drumKit;

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
