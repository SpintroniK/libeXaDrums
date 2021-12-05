/*
 * Config_api.hpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_API_CONFIG_CONFIG_API_HPP
#define LIBEXADRUMS_API_CONFIG_CONFIG_API_HPP

#include "Config_api.h"

#include "TriggerParameters_api.h"

namespace eXaDrumsApi
{

	inline void Config::SaveSensorsConfig()
	{
		Util::ErrorToException([&] { return this->SaveSensorsConfig_(); });
	}

	inline void Config::SaveTriggersConfig()
	{
		Util::ErrorToException([&] { return this->SaveTriggersConfig_(); });
	}

	inline void Config::LoadTriggersConfig() const
	{
		Util::ErrorToException([&] { return this->LoadTriggersConfig_(); });
	}

	inline void Config::LoadSpiDevConfig() const
	{
		Util::ErrorToException([&] { return this->LoadSpiDevConfig_(); });
	}

	inline void Config::SaveSpiDevConfig()
	{
		Util::ErrorToException([&] { return this->SaveSpiDevConfig_(); });
	}

	inline void Config::SaveCurrentAudioDeviceConfig() const
	{
		Util::ErrorToException([&] { return this->SaveCurrentAudioDeviceConfig_(); });
	}

	inline void Config::SaveAudioDeviceConfig(const AlsaParamsApi& params)
	{
		Util::ErrorToException([&] { return this->SaveAudioDeviceConfig_(params); });
	}

	inline void Config::ResetAudioDevice()
	{
		Util::ErrorToException([&] { return this->ResetAudioDevice_(); });
	}

	inline void Config::ExportConfig(const std::string& configDir, const std::string& outputFileName)
	{
		Util::ErrorToException([&] { return Config::ExportConfig_(configDir.c_str(), outputFileName.c_str()); });
	}


	inline void Config::ImportConfig(const std::string& configFile, const std::string& outputConfigDir, bool replace)
	{
		Util::ErrorToException([&] { return Config::ImportConfig_(configFile.c_str(), outputConfigDir.c_str(), replace); });
	}

	inline void Config::AddTrigger(const TriggerParameters& params)
	{
		Util::ErrorToException([&] { return this->AddTrigger_(params); });
	}

	inline void Config::DeleteTrigger(int sensorId)
	{
		Util::ErrorToException([&] { return this->DeleteTrigger_(sensorId); });
	}


	inline std::size_t Config::GetNbTriggers() const
	{
		size_t nb = 0;
		this->GetNbTriggers_(nb);
		return nb;
	}


	inline void Config::SetSensorsType(const std::string& type)
	{

		SetSensorsType_(type.c_str());
		return;
	}

	inline void Config::SetSensorsDataFolder(const std::string& folder) noexcept
	{

		SetSensorsDataFolder_(folder.c_str());
		return;
	}

	inline void Config::SetAudioDeviceParameters(const AlsaParamsApi& params)
	{

		Util::ErrorToException([&] { return SetAudioDeviceParameters_(params); });

		return;
	}

	inline void Config::SetTriggersParameters(const std::vector<TriggerParameters>& params)
	{

		SetTriggersParameters_(params.data(), params.size());

		return;
	}

	inline void Config::SetSpiDevParameters(const std::vector<SpiDevParameters>& params)
	{
		SetSpiDevParameters_(params.data(), params.size());
	}

	inline void Config::SetTriggerParameters(int triggerId, const TriggerParameters& params)
	{
		SetTriggerParameters_(triggerId, params);
	}

	inline std::vector<std::string> Config::GetSensorsTypes()
	{

		unsigned int size = 0;
		GetSensorsTypes_(nullptr, size);

		std::vector<const char*> data(size);

		GetSensorsTypes_(data.data(), size);

		std::vector<std::string> vec(size);
		std::copy(data.cbegin(), data.cend(), vec.begin());

		return vec;
	}

	inline std::vector<std::string> Config::GetTriggersTypes()
	{

		unsigned int size = 0;
		GetTriggersTypes_(nullptr, size);

		std::vector<const char*> data(size);

		GetTriggersTypes_(data.data(), size);

		std::vector<std::string> vec(size);
		std::copy(data.cbegin(), data.cend(), vec.begin());

		return vec;
	}

	inline std::vector<std::string> Config::GetTriggersResponses()
	{

		unsigned int size = 0;
		GetTriggersResponses_(nullptr, size);

		std::vector<const char*> data(size);

		GetTriggersResponses_(data.data(), size);

		std::vector<std::string> vec(size);
		std::copy(data.cbegin(), data.cend(), vec.begin());

		return vec;
	}

	inline std::vector<std::string> Config::GetAudioDevicesNames()
	{

		unsigned int size = 0;
		GetAudioDevicesNames_(nullptr, size);

		std::vector<const char*> data(size);

		GetAudioDevicesNames_(data.data(), size);

		std::vector<std::string> vec(size);
		std::copy(data.cbegin(), data.cend(), vec.begin());

		return vec;
	}

	inline std::vector<TriggerParameters> Config::GetTriggersParameters() const
	{

		unsigned int size = 0;
		GetTriggersParameters_(nullptr, size);

		std::vector<TriggerParameters> vec(size);
		GetTriggersParameters_(vec.data(), size);

		return vec;
	}

	inline std::vector<std::string> Config::GetSupportedSpiDevices()
	{
		unsigned int size{};
		GetSupportedSpiDevices_(nullptr, size);

		std::vector<const char*> data(size);
		GetSupportedSpiDevices_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline AlsaParamsApi Config::GetAudioDeviceParams() const noexcept
	{
		return GetAudioDeviceParams_();
	}


	inline std::vector<SpiDevParameters> Config::GetSpiDevicesParameters() const
	{

		unsigned int size = 0;
		GetSpiDevicesParameters_(nullptr, size);

		std::vector<SpiDevParameters> vec;
		vec.reserve(size);
		for(size_t i = 0; i < size; ++i)
		{
			vec.emplace_back("", -1, -1);
		}
		GetSpiDevicesParameters_(vec.data(), size);

		return vec;
	}

	inline std::string Config::GetSensorsType()
	{
		return std::string(GetSensorsType_());
	}

	inline std::string Config::GetSensorsDataFolder() const noexcept
	{
		return std::string(GetSensorsDataFolder_());
	}


	inline std::string Config::GetAudioDeviceName() const noexcept
	{
		return std::string(GetAudioDeviceName_());
	}


}  // namespace eXaDrumsApi



#endif /* LIBEXADRUMS_API_CONFIG_CONFIG_API_HPP */
