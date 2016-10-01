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


	std::ostream& operator<<(std::ostream& o, const InstrumentSoundType& x);

	InstrumentSoundType operator++(InstrumentSoundType& x);
	InstrumentSoundType operator*(InstrumentSoundType x);
	InstrumentSoundType begin(InstrumentSoundType x);
	InstrumentSoundType end(InstrumentSoundType x);

}


#endif /* SOURCE_SOUND_INSTRUMENTSOUNDTYPE_H_ */
