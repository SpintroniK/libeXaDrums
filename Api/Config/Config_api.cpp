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
#include "../../Util/ErrorHandling.h"
#include "../../Sound/Alsa/Alsa.h"
#include "../../Sound/Alsa/AlsaParameters.h"

#include "../eXaDrums.h"

#include <algorithm>
#include <iostream>

using namespace Util;

namespace eXaDrumsApi
{


	Config::Config(eXaDrums& drums) noexcept : drumKit(drums), module(*drums.drumModule.get())
	{

		RefreshSensorsConfig();

		return;
	}


	void Config::RefreshSensorsConfig() noexcept
	{

		this->sensorsConfig = module.GetSensorsConfig();

		return;
	}


	// Private Methods

	error Config::SaveSensorsConfig_()
	{

		std::string dir;
		module.GetDirectory(dir);

		return ExceptionToError([&]
		{
			DrumKit::TriggerManager::SaveSensorsConfig(dir, sensorsConfig);
			RestartModule();
		});
	}

	error Config::SaveTriggersConfig_()
	{

		std::string dir;
		module.GetDirectory(dir);

		// Conversion to internal type
		std::vector<DrumKit::TriggerParameters> trigsParams(triggersParameters.size());
		std::transform(triggersParameters.begin(), triggersParameters.end(), trigsParams.begin(), [](auto& tp) { return static_cast<DrumKit::TriggerParameters>(tp); });

		return ExceptionToError([&]
		{
			DrumKit::TriggerManager::SaveTriggersConfig(dir, trigsParams);
			RestartModule();
		});
	}

	error Config::LoadTriggersConfig_() const
	{

		std::string dir;
		module.GetDirectory(dir);

		// Load sensors config first
		IO::SensorsConfig sensorConfig;
		std::vector<DrumKit::TriggerParameters> trigsParams;

		return ExceptionToError([&]
		{
			DrumKit::TriggerManager::LoadSensorsConfig(dir, sensorConfig);
			DrumKit::TriggerManager::LoadTriggersConfig(dir, sensorConfig, trigsParams);

			// Conversion and copy of the triggers parameters
			this->triggersParameters.clear();
			this->triggersParameters.resize(trigsParams.size());
			std::transform(trigsParams.begin(), trigsParams.end(), triggersParameters.begin(), [](auto& tp) 
			{ 
				return static_cast<eXaDrumsApi::TriggerParameters>(tp); 
			});
		});
	}

	error Config::SaveCurrentAudioDeviceConfig_() const
	{

		Sound::AlsaParams params;
		params.device = alsaParams.device;
		params.sampleRate = alsaParams.sampleRate;
		params.nChannels = alsaParams.nChannels;
		params.capture = alsaParams.capture;
		params.bufferTime = alsaParams.bufferTime;
		params.periodTime = alsaParams.periodTime;

		return ExceptionToError([&] 
		{
			Sound::AlsaParameters::SaveAlsaParameters(drumKit.GetDataLocation() + eXaDrums::alsaConfigFile, params);
		});
	}

	error Config::SaveAudioDeviceConfig_(const AlsaParamsApi& params)
	{

		auto err = SetAudioDeviceParameters_(params);

		if(err.type!= error_type_success)
		{
			return err;
		}

		return SaveCurrentAudioDeviceConfig_();
	}

	error Config::ResetAudioDevice_()
	{
		return ExceptionToError([&]
		{
			this->drumKit.alsa.reset();

			// Load alsa parameters
			Sound::AlsaParams alsaParams;
			Sound::AlsaParameters::LoadAlsaParameters(drumKit.GetDataLocation() + eXaDrums::alsaConfigFile, alsaParams);

			// Create mixer and alsa
			this->drumKit.alsa = std::make_unique<Sound::Alsa>(alsaParams, this->drumKit.mixer);
		});
	}

	error Config::AddTrigger_(const TriggerParameters& params)
	{
		// Reload triggers config
		auto err = LoadTriggersConfig_();
		if(err.type!= error_type_success)
		{
			return err;
		}

		// Add trigger
		this->triggersParameters.push_back(params);

		// Save trigger config
		if(update_error(err, SaveTriggersConfig_()) != error_type_success)
		{
			return err;
		}

		// Restart module
		RestartModule();

		return err;
	}

	error Config::DeleteTrigger_(int sensorId)
	{

		// Reload triggers config
		auto err = LoadTriggersConfig_();
		if(err.type!= error_type_success)
		{
			return err;
		}

		// Remove trigger
		auto it = std::remove_if(triggersParameters.begin(), triggersParameters.end(), [&](const auto& tp) { return tp.sensorId == sensorId; });

		if(it != end(triggersParameters))
		{
			triggersParameters.erase(it);
		}
		else
		{
			return make_error("Could not delete trigger, as it does not exist.", error_type_warning);
		}
		

		// Save triggers config
		err = SaveTriggersConfig_();
		if(err.type!= error_type_success)
		{
			return err;
		}

		RestartModule();

		return make_error("", error_type_success);
	}

	void Config::SetSensorsType_(const char* type)
	{

		sensorsConfig.sensorType = Enums::ToElement<IO::SensorType>(std::string(type));
		return;
	}

	void Config::SetSensorsDataFolder_(const char* folder) noexcept
	{

		sensorsConfig.hddDataFolder = std::string(folder);
		return;
	}


	void Config::SetTriggersParameters_(const TriggerParameters* params, unsigned int size) noexcept
	{

		std::vector<TriggerParameters> trigParams(params, params + size);

		this->triggersParameters.clear();
		this->triggersParameters = trigParams;

		return;
	}

	error Config::SetAudioDeviceParameters_(const AlsaParamsApi& params)
	{

		this->alsaParams = params;
		std::string deviceName(params.device);

		// Replace device name by device id
		auto itDev = std::find_if(audioDevices.begin(), audioDevices.end(), [&](const auto& dev) { return deviceName == dev.first; });

		if(itDev != audioDevices.end())
		{
			std::strcpy(this->alsaParams.device, itDev->second.data());
		}
		else
		{
			return make_error(("Error: audio device " + deviceName + " not found.").data(), error_type_error);
		}

		return make_error("", error_type_success);
	}

	error Config::GetNbTriggers_(size_t& nb) const
	{
		auto error = this->LoadTriggersConfig_();
		
		if(error.type != error_type_success)
		{
			return error;
		}

		nb = static_cast<int>(triggersParameters.size());

		return make_error("", error_type_success);
	}

	error Config::ExportConfig_(const char* configDir, const char* outputFileName) noexcept
	{
		if(ZipDir(std::string{configDir}, std::string{outputFileName}))
		{
			return make_error("", error_type_success);
		}

		return make_error("Could not export configuration. Make sure that the source and destination folders exist.", error_type_warning);
	}


	error Config::ImportConfig_(const char* configFile, const char* outputConfigDir, bool replace) noexcept
	{
		if(UnzipDir(std::string{configFile}, std::string{outputConfigDir}, replace))
		{
			return make_error("", error_type_success);
		}

		return make_error("Cannot import configuration. Please check the file's integrity.", error_type_warning);
	}

	void Config::RestartModule()
	{

		bool isRestart = false;

		if(drumKit.isStarted.load())
		{
			ErrorToException([&] { return drumKit.Stop_(); });
			isRestart = true;
		}

		int kitId = module.GetKitId();

		module.ReloadTriggers();
		module.ReloadKits();

		module.SelectKit(kitId);

		if(isRestart)
		{
			ErrorToException([&] { return drumKit.Start_(); });
		}

		return;
	}

	void Config::SetTriggerParameters_(int triggerId, const TriggerParameters& params)
	{
		const auto triggerParams = static_cast<DrumKit::TriggerParameters>(params);

		module.SetTriggerParameters(triggerId, triggerParams);
	}

	void Config::GetSensorsTypes_(const char** types, unsigned int& size)
	{

		if(types == nullptr)
		{
			size = Enums::GetEnumVector<IO::SensorType>().size();
			return;
		}

		const std::vector<IO::SensorType>& vec = Enums::GetEnumVector<IO::SensorType>();

		this->sensorsTypes.clear();
		this->sensorsTypes.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->sensorsTypes.begin(), [](const IO::SensorType& t) { return Enums::ToString(t); });


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
			size = Enums::GetEnumVector<DrumKit::TriggerType>().size();
			return;
		}

		const std::vector<DrumKit::TriggerType>& vec = Enums::GetEnumVector<DrumKit::TriggerType>();

		this->triggersTypes.clear();
		this->triggersTypes.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->triggersTypes.begin(), [](const DrumKit::TriggerType& t) { return Enums::ToString(t); });

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
			size = Enums::GetEnumVector<DrumKit::CurveType>().size();
			return;
		}

		const std::vector<DrumKit::CurveType>& vec = Enums::GetEnumVector<DrumKit::CurveType>();

		this->triggersResponses.clear();
		this->triggersResponses.resize(vec.size());

		std::transform(vec.cbegin(), vec.cend(), this->triggersResponses.begin(), [](const DrumKit::CurveType& r) { return Enums::ToString(r); });

		unsigned int numElements = std::min<unsigned int>(size, triggersResponses.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			responses[i] = triggersResponses[i].c_str();
		}

		return;
	}

	void Config::GetAudioDevicesNames_(const char** dev, unsigned int& size)
	{

		const auto devices = Sound::Alsa::GetDevices();

		if(dev == nullptr)
		{
			size = devices.size();
			return;
		}

		this->audioDevices.clear();
		this->audioDevices.resize(devices.size());

		std::copy(devices.begin(), devices.end(), this->audioDevices.begin());

		unsigned int numElements = std::min<unsigned int>(size, audioDevices.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			dev[i] = audioDevices[i].first.data();
		}

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

		this->sensorType = Enums::ToString(this->sensorsConfig.sensorType);

		return this->sensorType.c_str();
	}

	const char* Config::GetSensorsDataFolder_() const noexcept
	{
		return this->sensorsConfig.hddDataFolder.c_str();
	}

	const char* Config::GetAudioDeviceName_() const noexcept
	{
		this->audioDeviceName = this->drumKit.GetAudioDeviceName();
		return this->audioDeviceName.data();
	}

	AlsaParamsApi Config::GetAudioDeviceParams_() const noexcept
	{
		AlsaParamsApi alsaParameters = static_cast<AlsaParamsApi>(this->drumKit.alsa->GetParameters());
		return alsaParameters;
	}


}
