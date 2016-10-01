/*
 * Enums.cpp
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#include "Enums.h"


namespace Util
{

	// Initialise vectors

	const std::vector<ClickType> Enums::clickTypes = Enums::GetClickTypes();
	const std::vector<InstrumentType> Enums::instrumentTypes = Enums::GetInstrumentTypes();
	const std::vector<TriggerLocation> Enums::triggerLocations = Enums::GetTriggerLocations();
	const std::vector<InstrumentSoundType> Enums::instrumentSoundsTypes = Enums::GetInstrumentSoundTypes();


	// Click types

	ClickType Enums::ClickTypeFromString(const std::string& s)
	{

		auto it = std::find_if(clickTypes.cbegin(), clickTypes.cend(), [&s](const ClickType& x) { std::stringstream ss; ss << x; return ss.str() == s; });

		return (*it);
	}

	std::string Enums::ClickTypeToString(const ClickType& x)
	{

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), x);

		std::stringstream ss;
		ss << (*it);

		return ss.str();
	}

	std::vector<ClickType> Enums::GetClickTypes()
	{

		if(clickTypes.empty())
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


	// Instrument types


	InstrumentType Enums::InstrumentTypeFromString(const std::string& s)
	{

		auto it = std::find_if(instrumentTypes.cbegin(), instrumentTypes.cend(), [&s](const InstrumentType& x) { std::stringstream ss; ss << x; return ss.str() == s; });

		return (*it);
	}


	std::string Enums::InstrumentTypeToString(const InstrumentType& x)
	{

		auto it = std::find(instrumentTypes.cbegin(), instrumentTypes.cend(), x);

		std::stringstream ss;
		ss << (*it);

		return ss.str();
	}


	std::vector<InstrumentType> Enums::GetInstrumentTypes()
	{

		if(instrumentTypes.empty())
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


	// Triggers locations

	TriggerLocation Enums::TriggerLocationFromString(const std::string& s)
	{

		auto it = std::find_if(triggerLocations.cbegin(), triggerLocations.cend(), [&s](const TriggerLocation& x) { std::stringstream ss; ss << x; return ss.str() == s; });

		return (*it);
	}

	std::string Enums::TriggerLocationToString(const TriggerLocation& x)
	{

		auto it = std::find(triggerLocations.cbegin(), triggerLocations.cend(), x);

		std::stringstream ss;
		ss << (*it);

		return ss.str();
	}


	std::vector<TriggerLocation> Enums::GetTriggerLocations()
	{

		if(triggerLocations.empty())
		{

			std::vector<TriggerLocation> v;

			for(auto const& t : TriggerLocation())
			{
				v.push_back(t);
			}

			return v;
		}
		else
		{
			return triggerLocations;
		}
	}


	// Instrument sounds types

	InstrumentSoundType Enums::InstrumentSoundTypeFromString(const std::string& s)
	{

		auto it = std::find_if(instrumentSoundsTypes.cbegin(), instrumentSoundsTypes.cend(), [&s](const InstrumentSoundType& x) { std::stringstream ss; ss << x; return ss.str() == s; });

		return (*it);
	}

	std::string Enums::InstrumentSoundTypeToString(const InstrumentSoundType& x)
	{

		auto it = std::find(instrumentSoundsTypes.cbegin(), instrumentSoundsTypes.cend(), x);

		std::stringstream ss;
		ss << (*it);

		return ss.str();
	}

	std::vector<InstrumentSoundType> Enums::GetInstrumentSoundTypes()
	{

		if(instrumentSoundsTypes.empty())
		{

			std::vector<InstrumentSoundType> v;

			for(auto const& t : InstrumentSoundType())
			{
				v.push_back(t);
			}

			return v;
		}
		else
		{
			return instrumentSoundsTypes;
		}
	}


}


