/*
 * Enums.cpp
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#include "Enums.h"


namespace Util
{


	const std::vector<ClickType> Enums::clickTypes = Enums::GetClickTypes();
	const std::vector<InstrumentType> Enums::instrumentTypes = Enums::GetInstrumentTypes();


	std::string Enums::ClickTypeToString(const ClickType& c)
	{

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), c);

		if(it != std::end(clickTypes))
		{

			std::stringstream ss;
			ss << (*it);

			return ss.str();
		}

		return std::string();
	}

	ClickType Enums::ClickTypeFromString(const std::string& s)
	{

		auto it = std::find_if(clickTypes.cbegin(), clickTypes.cend(), [&s](const ClickType& c) { std::stringstream ss; ss << c; return ss.str() == s; });

		if(it != std::end(clickTypes))
		{
			return (*it);
		}

		return ClickType::Last;
	}



	std::vector<ClickType> Enums::GetClickTypes()
	{

		if(clickTypes.size() == 0)
		{

			std::vector<ClickType> v;

			for(auto const& c : ClickType())
			{
				v.push_back(c);
			}

			return v;
		}
		else
		{
			return clickTypes;
		}
	}


	std::string Enums::InstrumentTypeToString(const InstrumentType& i)
	{

		auto it = std::find(instrumentTypes.cbegin(), instrumentTypes.cend(), i);

		if(it != std::end(instrumentTypes))
		{

			std::stringstream ss;
			ss << (*it);

			return ss.str();
		}

		return std::string();
	}

	InstrumentType Enums::InstrumentTypeFromString(const std::string& s)
	{

		auto it = std::find_if(instrumentTypes.cbegin(), instrumentTypes.cend(), [&s](const InstrumentType& i) { std::stringstream ss; ss << i; return ss.str() == s; });

		if(it != std::end(instrumentTypes))
		{
			return (*it);
		}

		return InstrumentType::Last;
	}

	std::vector<InstrumentType> Enums::GetInstrumentTypes()
	{

		if(instrumentTypes.size() == 0)
		{

			std::vector<InstrumentType> v;

			for(auto const& c : InstrumentType())
			{
				v.push_back(c);
			}

			return v;
		}
		else
		{
			return instrumentTypes;
		}
	}

}


