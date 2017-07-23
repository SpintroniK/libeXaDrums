/*
 * Config_api.cpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */


#include "Config_api.h"

#include "TriggerParameters_api.h"

#include "../../DrumKit/DrumModule/Module.h"
#include "../../DrumKit/Triggers/TriggerManager.h"
#include "../../Util/Enums.h"

#include "../eXaDrums.h"

#include <algorithm>

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

		DrumKit::TriggerManager::SaveSensorsConfig(dir, sensorsConfig);

		RestartModule();

		return;
	}

	void Config::RestartModule()
	{

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

	void Config::SaveTriggersConfig()
	{

		std::string dir;
		module.GetDirectory(dir);

		// Conversion to internal type
		std::vector<DrumKit::TriggerParameters> trigsParams(triggersParameters.size());
		std::transform(triggersParameters.begin(), triggersParameters.end(), trigsParams.begin(), [](eXaDrumsApi::TriggerParameters& tp) { return (DrumKit::TriggerParameters)tp; });

		DrumKit::TriggerManager::SaveTriggersConfig(dir, trigsParams);

		RestartModule();

		return;
	}

	void Config::LoadTriggersConfig()
	{

		std::string dir;
		module.GetDirectory(dir);

		// Load sensors config first
		IO::SensorsConfig sensorConfig;
		DrumKit::TriggerManager::LoadSensorsConfig(dir, sensorConfig);

		std::vector<DrumKit::TriggerParameters> trigsParams;
		DrumKit::TriggerManager::LoadTriggersConfig(dir, sensorConfig, trigsParams);

		// Conversion and copy of the triggers parameters
		this->triggersParameters.clear();
		this->triggersParameters.resize(trigsParams.size());
		std::transform(trigsParams.begin(), trigsParams.end(), triggersParameters.begin(), [](DrumKit::TriggerParameters& tp) { return (eXaDrumsApi::TriggerParameters)tp; });

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

	void Config::SetTriggersParameters_(const TriggerParameters* params, unsigned int size)
	{

		std::vector<TriggerParameters> trigParams(params, params + size);

		this->triggersParameters.clear();
		this->triggersParameters = trigParams;

		return;
	}

	void Config::GetSensorsTypes_(const char** types, unsigned int& size)
	{

		if(types == nullptr)
		{
			size = Enums<IO::SensorType>::GetEnumVector().size();
			return;
		}

		const std::vector<IO::SensorType>& vec = Enums<IO::SensorType>::GetEnumVector();

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

	void Config::GetTriggersTypes_(const char** types, unsigned int& size)
	{

		if(types == nullptr)
		{
			size = Enums<DrumKit::TriggerType>::GetEnumVector().size();
			return;
		}

		const std::vector<DrumKit::TriggerType>& vec = Enums<DrumKit::TriggerType>::GetEnumVector();

		this->triggersTypes.clear();
		this->triggersTypes.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->triggersTypes.begin(), [](const DrumKit::TriggerType& t) { return Enums<DrumKit::TriggerType>::ToString(t); });

		unsigned int numElements = std::min<unsigned int>(size, triggersTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			types[i] = triggersTypes[i].c_str();
		}

		return;
	}

	void Config::GetTriggersResponses_(const char** responses, unsigned int& size)
	{

		if(responses == nullptr)
		{
			size = Enums<DrumKit::CurveType>::GetEnumVector().size();
			return;
		}

		const std::vector<DrumKit::CurveType>& vec = Enums<DrumKit::CurveType>::GetEnumVector();

		this->triggersResponses.clear();
		this->triggersResponses.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->triggersResponses.begin(), [](const DrumKit::CurveType& r) { return Enums<DrumKit::CurveType>::ToString(r); });

		unsigned int numElements = std::min<unsigned int>(size, triggersResponses.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			responses[i] = triggersResponses[i].c_str();
		}

		return;
	}

	void Config::GetTriggersParameters_(TriggerParameters* const triggers, unsigned int& size) const
	{

		const std::vector<DrumKit::TriggerParameters>& trigsParams = this->module.GetTriggersParameters();

		if(triggers == nullptr)
		{
			size = trigsParams.size();
			return;
		}

		if(size != trigsParams.size())
		{
			throw -1;
		}

		std::copy(trigsParams.cbegin(), trigsParams.cend(), triggers);

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
