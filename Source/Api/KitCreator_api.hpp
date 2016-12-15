/*
 * KitCreator_api.hpp
 *
 *  Created on: 14 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_KITCREATOR_API_HPP_
#define SOURCE_API_KITCREATOR_API_HPP_

#include "KitCreator_api.h"

#include <vector>
#include <algorithm>

namespace eXaDrumsApi
{

	inline std::vector<int> KitCreator::GetTriggersIds() const
	{

		unsigned int size;
		GetTriggersIds_(nullptr, size);

		std::vector<int> trigsIds(size);
		GetTriggersIds_(trigsIds.data(), size);

		return trigsIds;
	}

	inline std::vector<std::string> KitCreator::GetSoundFiles()
	{

		unsigned int size;
		GetSoundFiles_((const char**)nullptr, size);

		std::vector<const char*> data(size);
		GetSoundFiles_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}


}



#endif /* SOURCE_API_KITCREATOR_API_HPP_ */
