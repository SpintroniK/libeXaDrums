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

		/**
		 * @brief Construct a new Config object
		 * 
		 * @param drums eXaDrums instance
		 */
		explicit Config(eXaDrums& drums) noexcept;

		/**
		 * @brief Destroy the Config object
		 * 
		 */
		~Config() = default;

		/**
		 * @brief Refresh sensors config internal variable
		 * 
		 */
		void RefreshSensorsConfig() noexcept;

		/**
		 * @brief Save current sensors configuration (restarts the module).
		 * 
		 */
		void SaveSensorsConfig();

		/**
		 * @brief Save current triggers configuration and restart module.
		 * 
		 */
		void SaveTriggersConfig();

		/**
		 * @brief Load triggers configuration.
		 * 
		 */
		void LoadTriggersConfig() const;

		/**
		 * @brief Save current audio device configuration.
		 * 
		 */
		void SaveCurrentAudioDeviceConfig() const;

		/**
		 * @brief Set audio device parameters and save configuration.
		 * 
		 * @param params Audio device parameters.
		 */
		void SaveAudioDeviceConfig(const AlsaParamsApi& params);

		/**
		 * @brief Restart audio device using saved configuration.
		 * 
		 */
		void ResetAudioDevice();

		// Config
		/**
		 * @brief Export configuration.
		 * 
		 * @param configDir Current configuration directory.
		 * @param outputFileName Output configuration backup file name.
		 */
		static void ExportConfig(const std::string& configDir, const std::string& outputFileName);

		/**
		 * @brief Import configuration.
		 * 
		 * @param configFile Backup configuration file path and name.
		 * @param outputConfigDir Output directory, where the configuration is to be extracted.
		 * @param replace Whether to replace existing files or not.
		 */
		static void ImportConfig(const std::string& configFile, const std::string& outputConfigDir, bool replace = false);

		// Triggers
		/**
		 * @brief Add a new trigger and save configuration.
		 * 
		 * @param params New trigger parameters.
		 */
		void AddTrigger(const TriggerParameters& params);

		/**
		 * @brief Delete a trigger and save configuration.
		 * 
		 * @param sensorId Id of the trigger to be deleted.
		 */
		void DeleteTrigger(int sensorId);

		/**
		 * @brief Get the number of triggers
		 * 
		 * @return std::size_t 
		 */
		std::size_t GetNbTriggers() const;

		// Mutators
		/**
		 * @brief Set the sensors sampling sate (for SPI sensors).
		 * 
		 * @param sRate Sampling frequency in Hz.
		 */
		void SetSensorsSamplingRate(int sRate) noexcept { sensorsConfig.samplingRate = sRate; }

		/**
		 * @brief Set the sensors resolution (For SPI or HDD sensors).
		 * 
		 * @param res Resolution in bits (up to 16).
		 */
		void SetSensorsResolution(int res) noexcept { sensorsConfig.resolution = res; }

		/**
		 * @brief Set the sensors type.
		 * 
		 * @param type Sensor type.
		 */
		void SetSensorsType(const std::string& type);

		/**
		 * @brief Set the sensor data folder (for HDD sensor).
		 * 
		 * @param folder Path to raw sensor data.
		 */
		void SetSensorsDataFolder(const std::string& folder) noexcept;

		/**
		 * @brief Set audio device parameters.
		 * 
		 * @param params Audio device parameters.
		 */
		void SetAudioDeviceParameters(const AlsaParamsApi& params);

		/**
		 * @brief Set all triggers parameters.
		 * 
		 * @param params Triggers parameters list.
		 */
		void SetTriggersParameters(const std::vector<TriggerParameters>& params);

		/**
		 * @brief Set trigger parameters.
		 * 
		 * @param triggerId Trigger id.
		 * @param params Trigger parameters.
		 */
		void SetTriggerParameters(int triggerId, const TriggerParameters& params);

		// Accessors
		/**
		 * @brief Get the sensors types list.
		 * 
		 * @return std::vector<std::string> List of sensors types.
		 */
		std::vector<std::string> GetSensorsTypes();

		/**
		 * @brief Get the triggers types list.
		 * 
		 * @return std::vector<std::string> List of triggers types.
		 */
		std::vector<std::string> GetTriggersTypes();

		/**
		 * @brief Get the triggers response curves types.
		 * 
		 * @return std::vector<std::string> List of response curves.
		 */
		std::vector<std::string> GetTriggersResponses();

		/**
		 * @brief Get the available audio devices names.
		 * 
		 * @return std::vector<std::string> List of audio devices.
		 */
		std::vector<std::string> GetAudioDevicesNames();

		/**
		 * @brief Get triggers parameters list.
		 * 
		 * @return std::vector<TriggerParameters> List of triggers parameters.
		 */
		std::vector<TriggerParameters> GetTriggersParameters() const;

		/**
		 * @brief Get sensor type.
		 * 
		 * @return std::string Sensor type name.
		 */
		std::string GetSensorsType();

		/**
		 * @brief Get the (HDD) sensor data folder location.
		 * 
		 * @return std::string Data folder path.
		 */
		std::string GetSensorsDataFolder() const noexcept;

		/**
		 * @brief Get the audio device name.
		 * 
		 * @return std::string Audio device name.
		 */
		std::string GetAudioDeviceName() const noexcept;

		/**
		 * @brief Get audio device parameters.
		 * 
		 * @return AlsaParamsApi Audio device parameters.
		 */
		AlsaParamsApi GetAudioDeviceParams() const noexcept;


		/**
		 * @brief Get the (SPI) sensor sampling rate.
		 * 
		 * @return int Sampling frequency in Hz.
		 */
		int GetSensorsSamplingRate() const noexcept { return sensorsConfig.samplingRate; }

		/**
		 * @brief Get the (SPI) sensor resolution.
		 * 
		 * @return int Resolution in bits.
		 */
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
		static Util::error ImportConfig_(const char* configFile, const char* outputConfigDir, bool replace) noexcept;

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
