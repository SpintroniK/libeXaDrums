/*
 * InstrumentSoundType.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: jeremy
 */


#include "InstrumentSoundType.h"


namespace Sound
{


	std::ostream& operator<<(std::ostream& o, const InstrumentSoundType& x)
	{

		std::string os;

		switch (x)
		{

		case InstrumentSoundType::Default:		os = "DrumHead";	break;
		case InstrumentSoundType::RimShot:		os = "RimShot";		break;
		case InstrumentSoundType::ClosingHiHat:	os = "Rim";			break;


		default: break;

		}

		return o << os;
	}

	InstrumentSoundType operator++(InstrumentSoundType& x) { return x = (InstrumentSoundType)(std::underlying_type<InstrumentSoundType>::type(x) + 1); };
	InstrumentSoundType operator*(InstrumentSoundType x) { return x; };
	InstrumentSoundType begin(InstrumentSoundType x) { return InstrumentSoundType::First; };
	InstrumentSoundType end(InstrumentSoundType x) { InstrumentSoundType l = InstrumentSoundType::Last; return ++l; };


}
