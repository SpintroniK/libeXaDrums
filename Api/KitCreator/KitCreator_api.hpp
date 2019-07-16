/*
 * KitCreator_api.hpp
 *
 *  Created on: 14 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_KITCREATOR_KITCREATOR_API_HPP_
#define SOURCE_API_KITCREATOR_KITCREATOR_API_HPP_

#include "KitCreator_api.h"

#include <vector>
#include <algorithm>

namespace eXaDrumsApi
{

	inline void KitCreator::CreateFromModel(const char* loc)
	{
		Util::ErrorToException([&] { return this->CreateFromModel_(loc); });
	}

	inline void KitCreator::SaveKit(const char* file) const
	{
		Util::ErrorToException([&] { return this->SaveKit_(file); });
	}

	inline void KitCreator::SaveKit() const
	{
		Util::ErrorToException([&] { return this->SaveKit_(); });
	}

	inline void KitCreator::SetInstrumentName(const char* name)
	{
		Util::ErrorToException([&] { return this->SetInstrumentName_(name); });
	}

	inline void KitCreator::SetInstrumentName(int id, const char* name)
	{
		Util::ErrorToException([&] { return this->SetInstrumentName_(id, name); });
	}

	inline void KitCreator::SetInstrumentTriggersIdsAndLocs(int id, const std::vector<std::pair<int, std::string>>& trigsIdsAndLocs)
	{

		// Retrieve triggers ids
		std::vector<int> ids;
		std::transform(trigsIdsAndLocs.cbegin(), trigsIdsAndLocs.cend(), std::back_inserter(ids), [](const std::pair<int, std::string>& p) { return p.first; });


		// Retrieve triggers locations
		std::vector<std::string> trigsLocs;
		std::transform(trigsIdsAndLocs.cbegin(), trigsIdsAndLocs.cend(), std::back_inserter(trigsLocs), [](const std::pair<int, std::string>& p) { return p.second; });

		// Create trigger locations pointers
		std::vector<const char*> locs(trigsLocs.size());
		std::transform(trigsLocs.cbegin(), trigsLocs.cend(), locs.begin(), [](const std::string& s) { return s.c_str();});

		SetInstrumentTriggersIdsAndLocs_(id, ids.data(), locs.data(), trigsIdsAndLocs.size());

		return;
	}

	inline void KitCreator::SetInstrumentSoundsTypesAndLocs(int id, const std::vector<std::pair<std::string, std::string>>& sndTypesAndLocs)
	{

		// Retrieve sounds types
		std::vector<std::string> sndTypes;
		std::transform(sndTypesAndLocs.cbegin(), sndTypesAndLocs.cend(), std::back_inserter(sndTypes), [](const std::pair<std::string, std::string>& p){ return p.first; });

		// Retrieve sounds locations
		std::vector<std::string> sndLocs;
		std::transform(sndTypesAndLocs.cbegin(), sndTypesAndLocs.cend(), std::back_inserter(sndLocs), [](const std::pair<std::string, std::string>& p){ return p.second; });

		// Create sound types pointers
		std::vector<const char*> types(sndTypes.size());
		std::transform(sndTypes.cbegin(), sndTypes.cend(), types.begin(), [](const std::string& s) { return s.c_str(); });

		// Create sound locations pointers
		std::vector<const char*> locs(sndLocs.size());
		std::transform(sndLocs.cbegin(), sndLocs.cend(), locs.begin(), [](const std::string& s) { return s.c_str(); });

		SetInstrumentSoundsTypesAndLocs_(id, types.data(), locs.data(), sndTypesAndLocs.size());

		return;
	}

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

	/*inline std::vector<std::string> KitCreator::GetSoundsFiles()
	{

		unsigned int size;
		GetSoundFiles_(nullptr, size);

		std::vector<const char*> data(size);
		GetSoundFiles_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}*/

	inline std::vector<std::string> KitCreator::GetSoundsTypes(const std::string& instrumentType)
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

	inline std::vector<std::string> KitCreator::GetTriggersLocations(const std::string& instrumentType)
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



#endif /* SOURCE_API_KITCREATOR_KITCREATOR_API_HPP_ */
