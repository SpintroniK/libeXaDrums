/*
 * Config_api.hpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_CONFIG_API_HPP_
#define SOURCE_API_CONFIG_CONFIG_API_HPP_

#include "Config_api.h"

#include "TriggerParameters_api.h"

namespace eXaDrumsApi
{

	inline void Config::SetSensorsType(const std::string& type)
	{

		SetSensorsType_(type.c_str());
		return;
	}

	inline void Config::SetSensorsDataFolder(const std::string& folder)
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

	inline AlsaParamsApi Config::GetAudioDeviceParams() const
	{

		return GetAudioDeviceParams_();
	}

	inline std::string Config::GetSensorsType()
	{
		return std::string(GetSensorsType_());
	}

	inline std::string Config::GetSensorsDataFolder() const
	{
		return std::string(GetSensorsDataFolder_());
	}


	inline std::string Config::GetAudioDeviceName()
	{
		return std::string(GetAudioDeviceName_());
	}


}  // namespace eXaDrumsApi



#endif /* SOURCE_API_CONFIG_CONFIG_API_HPP_ */
