/*
 * TriggerLocation.h
 *
 *  Created on: 8 Mar 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_

#include <string>
#include <sstream>
#include <type_traits>


namespace DrumKit
{

	enum class TriggerLocation
	{

		DrumHead,
		Rim,

		First = DrumHead,
		Last = Rim

	};


	inline std::ostream& operator<<(std::ostream& o, const TriggerLocation& x)
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


	inline TriggerLocation operator++(TriggerLocation& x) { return x = static_cast<TriggerLocation>(std::underlying_type_t<TriggerLocation>(x) + 1); };
	inline TriggerLocation operator*(TriggerLocation i) { return i; };
	inline TriggerLocation begin(TriggerLocation x) { return TriggerLocation::First; };
	inline TriggerLocation end(TriggerLocation x) { TriggerLocation l = TriggerLocation::Last; return ++l; };


	inline std::istream& operator>>(std::istream& is, TriggerLocation& x)
	{
		return Util::StreamToEnum(is, x);
	}

}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_ */
