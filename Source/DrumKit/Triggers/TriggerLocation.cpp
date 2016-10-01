/*
 * TriggerLocation.cpp
 *
 *  Created on: 1 Oct 2016
 *      Author: jeremy
 */


#include "TriggerLocation.h"


namespace DrumKit
{


	std::ostream& operator<<(std::ostream& o, const TriggerLocation& x)
	{

		std::string os;

		switch (x)
		{

		case TriggerLocation::DrumHead:	os = "DrumHead";	break;
		case TriggerLocation::Rim:		os = "Rim";			break;


		default: break;

		}

		return o << os;
	}

	TriggerLocation operator++(TriggerLocation& x) { return x = (TriggerLocation)(std::underlying_type<TriggerLocation>::type(x) + 1); };
	TriggerLocation operator*(TriggerLocation i) { return i; };
	TriggerLocation begin(TriggerLocation x) { return TriggerLocation::First; };
	TriggerLocation end(TriggerLocation x) { TriggerLocation l = TriggerLocation::Last; return ++l; };


}

