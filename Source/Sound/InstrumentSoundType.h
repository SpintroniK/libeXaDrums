/*
 * InstrumentSoundType.h
 *
 *  Created on: 15 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_INSTRUMENTSOUNDTYPE_H_
#define SOURCE_SOUND_INSTRUMENTSOUNDTYPE_H_

#include <string>
#include <sstream>
#include <type_traits>

namespace Sound
{

	enum class InstrumentSoundType
	{

		Default,
		RimShot,
		ClosingHiHat,

		First = Default,
		Last = ClosingHiHat

	};


	inline std::ostream& operator<<(std::ostream& o, const InstrumentSoundType& x)
	{

		std::string os;

		switch (x)
		{

		case InstrumentSoundType::Default:		os = "DrumHead";	break;
		case InstrumentSoundType::RimShot:		os = "RimShot";		break;
		case InstrumentSoundType::ClosingHiHat:	os = "ClosingHiHat";break;


		default: break;

		}

		return o << os;
	}

	inline InstrumentSoundType operator++(InstrumentSoundType& x) { return x = (InstrumentSoundType)(std::underlying_type<InstrumentSoundType>::type(x) + 1); };
	inline InstrumentSoundType operator*(InstrumentSoundType x) { return x; };
	inline InstrumentSoundType begin(InstrumentSoundType x) { return InstrumentSoundType::First; };
	inline InstrumentSoundType end(InstrumentSoundType x) { InstrumentSoundType l = InstrumentSoundType::Last; return ++l; };

}


#endif /* SOURCE_SOUND_INSTRUMENTSOUNDTYPE_H_ */
