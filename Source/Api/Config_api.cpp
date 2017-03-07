/*
 * Config_api.cpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */


#include "Config_api.h"

#include "../DrumKit/DrumModule/Module.h"
#include "../DrumKit/Triggers/TriggerManager.h"
#include "../Util/Enums.h"

#include "eXaDrums.h"

#include <algorithm>

using namespace DrumKit;
using namespace Util;


namespace eXaDrumsApi
{


	Config::Config(eXaDrums& drums) : drumKit(drums), module(*drums.drumModule.get())
	{

		RefreshSensorsConfig();

		return;
	}


	void Config::RefreshSensorsConfig()
	{

		this->sensorsConfig = module.GetSensorsConfig();

		return;
	}

	void Config::SaveSensorsConfig()
	{

		std::string dir;
		module.GetDirectory(dir);

		TriggerManager::SaveSensorsConfig(dir, sensorsConfig);

		bool isRestart = false;

		if(drumKit.isStarted.load())
		{
			drumKit.Stop();
			isRestart = true;
		}

		int kitId = module.GetKitId();

		module.ReloadTriggers();
		module.ReloadKits();

		module.SelectKit(kitId);

		if(isRestart)
		{
			drumKit.Start();
		}

		return;
	}



	// Private Methods

	void Config::SetSensorsType_(const char* type)
	{

		sensorsConfig.sensorType = Enums<IO::SensorType>::ToElement(std::string(type));
		return;
	}

	void Config::SetSensorsDataFolder_(const char* folder)
	{

		sensorsConfig.hddDataFolder = std::string(folder);
		return;
	}

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

	const char* Config::GetSensorsType_()
	{

		this->sensorType = Enums<IO::SensorType>::ToString(this->sensorsConfig.sensorType);

		return this->sensorType.c_str();
	}

	const char* Config::GetSensorsDataFolder_() const
	{
		return this->sensorsConfig.hddDataFolder.c_str();
	}


}
