/*
 * Enums.hpp
 *
 *  Created on: 4 Jan 2017
 *      Author: jeremy
 */

#include <sstream>
#include <algorithm>

namespace Util
{

	template<typename T>
	std::string Enums<T>::ToString(const T& e)
	{

		std::stringstream ss;

		for (const auto& c : T())
		{
			if(c == e)
			{
				ss << e;
				return ss.str();
			}
		}

		//XXX Temporary (can't throw because of unfinished stuff).
		ss << T::First;
		return ss.str();
	}


	template<typename T>
	T Enums<T>::ToElement(const std::string& s)
	{

		for (const auto& c : T())
		{
			std::stringstream ss;
			ss << c;

			if(ss.str() == s)
			{
				return c;
			}
		}

		//XXX Temporary (can't throw because of unfinished stuff).
		return T::First;
	}


	template<typename T>
	std::vector<T> Enums<T>::GetEnumVector()
	{

		std::vector<T> v;

		for (const auto& c : T())
		{
			v.push_back(c);
		}

		return v;
	}



}
