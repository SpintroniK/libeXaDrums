/*
 * InstrumentTypes.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_


#include <vector>
#include <algorithm>
#include <sstream>


namespace DrumKit
{

	enum class InstrumentType
	{

		TestDrum,
		Drum,
		Cymbal,
		HiHat,
		BassDrum,

		First = TestDrum,
		Last = Cymbal

	};


	std::ostream& operator<<(std::ostream& o, const InstrumentType& x);

	inline InstrumentType operator++(InstrumentType& x) { return x = (InstrumentType)(std::underlying_type<InstrumentType>::type(x) + 1); };
	InstrumentType operator*(InstrumentType i);
	InstrumentType begin(InstrumentType x);
	InstrumentType end(InstrumentType x);


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTTYPE_H_ */
