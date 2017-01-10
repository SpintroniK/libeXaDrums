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

	inline std::string KitCreator::GetInstrumentType(int i)
	{
		return std::string(GetInstrumentType_(i));
	}

	inline std::vector<int> KitCreator::GetInstrumentTriggersIds(int i) const
	{

		unsigned int size;
		GetInstrumentTriggersIds_(i, nullptr, size);

		std::vector<int> trigsIds(size);
		GetInstrumentTriggersIds_(i, trigsIds.data(), size);

		return trigsIds;
	}

	inline std::vector<int> KitCreator::GetTriggersIds() const
	{

		unsigned int size;
		GetTriggersIds_(nullptr, size);

		std::vector<int> trigsIds(size);
		GetTriggersIds_(trigsIds.data(), size);

		return trigsIds;
	}

	inline std::vector<std::string> KitCreator::GetInstrumentTriggersLocations(int i)
	{

		unsigned int size;
		GetInstrumentTriggersLocations_(i, nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentTriggersLocations_(i, data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetInstrumentSoundsTypes(int i)
	{

		unsigned int size;
		GetInstrumentSoundsTypes_(i, nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentSoundsTypes_(i, data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetInstrumentSoundsLocs(int i)
	{

		unsigned int size;
		GetInstrumentSoundsLocs_(i, nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentSoundsLocs_(i, data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetSoundsFiles()
	{

		unsigned int size;
		GetSoundFiles_(nullptr, size);

		std::vector<const char*> data(size);
		GetSoundFiles_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetSoundsTypes(const std::string instrumentType)
	{

		unsigned int size;
		GetSoundTypes_(instrumentType.c_str(), nullptr, size);

		std::vector<const char*> data(size);
		GetSoundTypes_(instrumentType.c_str(), data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetInstrumentsTypes()
	{

		unsigned int size;
		GetInstrumentsTypes_(nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentsTypes_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetInstrumentsNames()
	{

		unsigned int size;
		GetInstrumentsNames_(nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentsNames_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> KitCreator::GetTriggersLocations(const std::string instrumentType)
	{

		unsigned int size;
		GetTriggersLocations_(instrumentType.c_str(), nullptr, size);

		std::vector<const char*> data(size);
		GetTriggersLocations_(instrumentType.c_str(), data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}


}



#endif /* SOURCE_API_KITCREATOR_API_HPP_ */
