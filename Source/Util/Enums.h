/*
 * Enums.h
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_ENUMS_H_
#define SOURCE_UTIL_ENUMS_H_


#include "../Metronome/ClickTypes.h"
#include "../DrumKit/Instruments/InstrumentType.h"

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

		// Click type
		static std::string ClickTypeToString(const ClickType& c);
		static ClickType ClickTypeFromString(const std::string& s);
		static std::vector<ClickType> GetClickTypes();

		// Instrument type
		static InstrumentType InstrumentTypeFromString(const std::string& s);
		static std::string InstrumentTypeToString(const InstrumentType& s);
		static std::vector<InstrumentType> GetInstrumentTypes();

	private:

		Enums(){};
		virtual ~Enums(){};


		static const std::vector<ClickType> clickTypes;
		static const std::vector<InstrumentType> instrumentTypes;


	};



}


#endif /* SOURCE_UTIL_ENUMS_H_ */
