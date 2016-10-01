/*
 * InstrumentType.cpp
 *
 *  Created on: 30 Sep 2016
 *      Author: jeremy
 */


#include "InstrumentType.h"

namespace DrumKit
{


	std::ostream& operator<<(std::ostream& o, const InstrumentType& x)
	{

		std::string os;

		switch (x)
		{

		case InstrumentType::TestDrum:	os = "TestDrum"; 	break;
		case InstrumentType::Drum:	 	os = "Drum"; 		break;
		case InstrumentType::Cymbal:	os = "Cymbal"; 		break;
		case InstrumentType::HiHat:		os = "HiHat"; 		break;
		case InstrumentType::BassDrum:	os = "BassDrum"; 	break;


		default: break;

		}

		return o << os;
	}

	InstrumentType operator++(InstrumentType& x) { return x = (InstrumentType)(std::underlying_type<InstrumentType>::type(x) + 1); };
	InstrumentType operator*(InstrumentType i) { return i; };
	InstrumentType begin(InstrumentType x) { return InstrumentType::First; };
	InstrumentType end(InstrumentType x) { InstrumentType l = InstrumentType::Last; return ++l; };


}
