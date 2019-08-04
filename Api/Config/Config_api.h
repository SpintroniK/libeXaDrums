/*
 * Config_api.h
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_CONFIG_API_H_
#define SOURCE_API_CONFIG_CONFIG_API_H_

#include "../../IO/SensorsConfig.h"
#include "../../Util/ErrorHandling.h"
#include "../../Util/Zip.h"

#include "AlsaParams_api.h"

#include <vector>
#include <string>

namespace DrumKit { class Module; }
namespace eXaDrumsApi{ class eXaDrums; struct TriggerParameters; }

namespace eXaDrumsApi
{

	class Config
	{

	public:

		explicit Config(eXaDrums& drums) noexcept;
		~Config() = default;

		void RefreshSensorsConfig() noexcept;
		void SaveSensorsConfig();
		void SaveTriggersConfig();
		void LoadTriggersConfig() const;
		void SaveCurrentAudioDeviceConfig() const;
		void SaveAudioDeviceConfig(const AlsaParamsApi& params);
		void ResetAudioDevice();

		// Config
		static void ExportConfig(const std::string& configDir, const std::string& outputFileName);
		static void ImportConfig(const std::string& configFile, const std::string& outputConfigDir);

		// Triggers
		void AddTrigger(const TriggerParameters& params);
		void DeleteTrigger(int sensorId);
		std::size_t GetNbTriggers() const;

		// Mutators
		void SetSensorsSamplingRate(int sRate) noexcept { sensorsConfig.samplingRate = sRate; }
		void SetSensorsResolution(int res) noexcept { sensorsConfig.resolution = res; }
		void SetSensorsType(const std::string& type);
		void SetSensorsDataFolder(const std::string& folder) noexcept;
		void SetAudioDeviceParameters(const AlsaParamsApi& params);
		void SetTriggersParameters(const std::vector<TriggerParameters>& params);
		void SetTriggerParameters(int triggerId, const TriggerParameters& params);

		// Accessors
		std::vector<std::string> GetSensorsTypes();
		std::vector<std::string> GetTriggersTypes();
		std::vector<std::string> GetTriggersResponses();
		std::vector<std::string> GetAudioDevicesNames();
		std::vector<TriggerParameters> GetTriggersParameters() const;

		std::string GetSensorsType();
		std::string GetSensorsDataFolder() const noexcept;
		std::string GetAudioDeviceName() const noexcept;
		AlsaParamsApi GetAudioDeviceParams() const noexcept;

		int GetSensorsSamplingRate() const noexcept { return sensorsConfig.samplingRate; }
		int GetSensorsResolution() const noexcept { return sensorsConfig.resolution; }

	private:

		Util::error SaveSensorsConfig_();
		Util::error SaveTriggersConfig_();
		Util::error LoadTriggersConfig_() const;
		Util::error SaveCurrentAudioDeviceConfig_() const;
		Util::error SaveAudioDeviceConfig_(const AlsaParamsApi& params);
		Util::error ResetAudioDevice_();
		Util::error AddTrigger_(const TriggerParameters& params);
		Util::error DeleteTrigger_(int sensorId);
		Util::error SetAudioDeviceParameters_(const AlsaParamsApi& params);
		Util::error GetNbTriggers_(size_t& nb) const;

		static Util::error ExportConfig_(const char* configDir, const char* outputFileName) noexcept;
		static Util::error ImportConfig_(const char* configFile, const char* outputConfigDir) noexcept;

		void RestartModule();

		void SetSensorsType_(const char* type);
		void SetSensorsDataFolder_(const char* folder) noexcept;
		void SetAudioDeviceParameters_(const char* name);
		void SetTriggersParameters_(const TriggerParameters* params, unsigned int size) noexcept;
		void SetTriggerParameters_(int triggerId, const TriggerParameters& params);

		const char* GetSensorsType_();
		const char* GetSensorsDataFolder_() const noexcept;
		const char* GetAudioDeviceName_() const noexcept;

		AlsaParamsApi GetAudioDeviceParams_() const noexcept;

		void GetSensorsTypes_(const char** types, unsigned int& size);
		void GetTriggersTypes_(const char** types, unsigned int& size);
		void GetTriggersResponses_(const char** responses, unsigned int& size);
		void GetAudioDevicesNames_(const char** devices, unsigned int& size);
		void GetTriggersParameters_(TriggerParameters* const triggers, unsigned int& size) const;

		eXaDrums& drumKit;
		DrumKit::Module& module;

		// Alsa config
		mutable AlsaParamsApi alsaParams;

		// Sensors config
		IO::SensorsConfig sensorsConfig;

		// Triggers config
		mutable std::vector<TriggerParameters> triggersParameters;

		// Local copies of items
		std::string sensorType;
		mutable std::string audioDeviceName;

		// Local copies of enums
		std::vector<std::string> sensorsTypes;
		std::vector<std::string> triggersTypes;
		std::vector<std::string> triggersResponses;
		std::vector<std::pair<std::string, std::string>> audioDevices;

	};

}

#include "Config_api.hpp"

#endif /* SOURCE_API_CONFIG_CONFIG_API_H_ */
