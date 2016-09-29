/*
 * Enums.cpp
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#include "Enums.h"


namespace Util
{

	const std::vector<clickType> Enums::clickTypes = Enums::GetClickTypesVector();

	std::string Enums::ClickTypeToString(const clickType& c)
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

	clickType Enums::ClickTypeFromString(const std::string& s)
	{

		auto it = std::find_if(clickTypes.cbegin(), clickTypes.cend(), [&s](const clickType& c) { std::stringstream ss; ss << c; return ss.str() == s; });

		if(it != std::end(clickTypes))
		{
			return (*it);
		}

		return clickType::Last;
	}



	std::vector<clickType> Enums::GetClickTypesVector()
	{

		if(clickTypes.size() == 0)
		{

			std::vector<clickType> v;

			for(auto const& c : clickType())
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

}


