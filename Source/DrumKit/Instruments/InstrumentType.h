/*
 * InstrumentTypes.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_


#include <sstream>
#include <string>
#include <type_traits>

namespace DrumKit
{

	enum class InstrumentType
	{

		TestDrum,
		Pad,
		Drum,
		Cymbal,
		HiHat,
		BassDrum,

		First = TestDrum,
		Last = BassDrum

	};


	inline std::ostream& operator<<(std::ostream& o, const InstrumentType& x)
	{

		std::string os;

		switch (x)
		{

		case InstrumentType::TestDrum:	os = "TestDrum"; 	break;
		case InstrumentType::Pad:	 	os = "Pad"; 		break;
		case InstrumentType::Drum:	 	os = "Drum"; 		break;
		case InstrumentType::Cymbal:	os = "Cymbal"; 		break;
		case InstrumentType::HiHat:		os = "HiHat"; 		break;
		case InstrumentType::BassDrum:	os = "BassDrum"; 	break;


		default: break;

		}

		return o << os;
	}

	inline InstrumentType operator++(InstrumentType& x) { return x = (InstrumentType)(std::underlying_type<InstrumentType>::type(x) + 1); };
	inline InstrumentType operator*(InstrumentType i) { return i; };
	inline InstrumentType begin(InstrumentType x) { return InstrumentType::First; };
	inline InstrumentType end(InstrumentType x) { InstrumentType l = InstrumentType::Last; return ++l; };


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_ */
