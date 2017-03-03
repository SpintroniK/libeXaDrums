/*
 * Config_api.cpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */


#include "Config_api.h"

#include "../DrumKit/DrumModule/Module.h"
#include "../Util/Enums.h"

#include "eXaDrums.h"

#include <algorithm>

using namespace Util;

namespace eXaDrumsApi
{


	Config::Config(eXaDrums& drums) : drumKit(drums)
	{

		RefreshSesorsConfig();

		return;
	}


	void Config::RefreshSesorsConfig()
	{

		this->sensorsConfig = drumKit.drumModule->GetSensorsConfig();

		return;
	}


	// Private Methods

	void Config::GetSensorsTypes_(const char** types, unsigned int& size)
	{

		if(types == nullptr)
		{
			size = Enums<IO::SensorType>::GetEnumVector().size();
			return;
		}

		std::vector<IO::SensorType> vec = Enums<IO::SensorType>::GetEnumVector();

		this->sensorsTypes.clear();
		this->sensorsTypes.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->sensorsTypes.begin(), [](const IO::SensorType& t) { return Enums<IO::SensorType>::ToString(t); });


		unsigned int numElements = std::min<unsigned int>(size, sensorsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			types[i] = sensorsTypes[i].c_str();
		}

		return;
	}

	const char* Config::GetSensorsType_() const
	{
		return Enums<IO::SensorType>::ToString(this->sensorsConfig.sensorType).c_str();
	}


}
