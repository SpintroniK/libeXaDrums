/*
 * Config_api.hpp
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_API_HPP_
#define SOURCE_API_CONFIG_API_HPP_

#include "Config_api.h"

namespace eXaDrumsApi
{

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

	inline std::string Config::GetSensorsType()
	{
		return std::string(GetSensorsType_());
	}


}  // namespace eXaDrumsApi



#endif /* SOURCE_API_CONFIG_API_HPP_ */
