/*
 * Enums.h
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_ENUMS_H_
#define SOURCE_UTIL_ENUMS_H_


#include "../Metronome/ClickTypes.h"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace DrumKit;

namespace Util
{


	class Enums
	{

	public:

		static std::string ClickTypeToString(const ClickType& c);
		static ClickType ClickTypeFromString(const std::string& s);
		static std::vector<ClickType> GetClickTypesVector();

	private:

		Enums(){};
		virtual ~Enums(){};


		static const std::vector<ClickType> clickTypes;


	};



}


#endif /* SOURCE_UTIL_ENUMS_H_ */
