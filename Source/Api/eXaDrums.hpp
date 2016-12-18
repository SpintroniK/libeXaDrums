/*
 * eXaDrums.hpp
 *
 *  Created on: 18 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMS_HPP_
#define SOURCE_API_EXADRUMS_HPP_


#include "eXaDrums.h"


namespace eXaDrumsApi
{

	inline std::vector<std::string> eXaDrums::GetClicksTypes()
	{

		unsigned int size;
		GetClicksTypes_(nullptr, size);

		std::vector<const char*> data(size);
		GetClicksTypes_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<int> eXaDrums::GetRhythms() const
	{

		unsigned int size;
		GetRhythms_(nullptr, size);

		std::vector<int> rhythms(size);
		GetRhythms_(rhythms.data(), size);

		return rhythms;
	}

	inline std::vector<int> eXaDrums::GetBpms() const
	{

		unsigned int size;
		GetBpms_(nullptr, size);

		std::vector<int> bpms(size);
		GetBpms_(bpms.data(), size);

		return bpms;
	}

	inline std::vector<std::string> eXaDrums::GetKitsNames()
	{

		unsigned int size;
		GetKitsNames_(nullptr, size);

		std::vector<const char*> data(size);
		GetKitsNames_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<std::string> eXaDrums::GetInstrumentsNames()
	{

		unsigned int size;
		GetInstrumentsNames_(nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentsNames_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}


}


#endif /* SOURCE_API_EXADRUMS_HPP_ */
