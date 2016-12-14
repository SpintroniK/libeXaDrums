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

namespace eXaDrumsApi
{

	inline std::vector<int> KitCreator::GetTriggersIds() const
	{

		int size;
		GetTriggersIds_(nullptr, size);

		std::vector<int> trigsIds(size);
		GetTriggersIds_(trigsIds.data(), size);

		return trigsIds;
	}



}



#endif /* SOURCE_API_KITCREATOR_API_HPP_ */
