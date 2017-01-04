/*
 * Enums.h
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_ENUMS_H_
#define SOURCE_UTIL_ENUMS_H_

#include <string>
#include <vector>

namespace Util
{

	template<typename T>
	class Enums
	{

	public:

		static std::string ToString(const T& e);
		static T ToElement(const std::string& s);
		static std::vector<T> GetEnumVector();


	private:

		Enums(){};
		virtual ~Enums(){};

	};

}

#include "Enums.hpp"

#endif /* SOURCE_UTIL_ENUMS_H_ */
