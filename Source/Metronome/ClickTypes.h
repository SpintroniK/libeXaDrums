/*
 * clickTypes.h
 *
 *  Created on: 28 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_CLICKTYPES_H_
#define SOURCE_METRONOME_CLICKTYPES_H_

#include <vector>
#include <algorithm>
#include <sstream>

namespace DrumKit
{

	enum class ClickType
	{

		Sine,
		Square,

		First = Sine,
		Last = Square

	};

	std::ostream& operator<<(std::ostream& o, const ClickType& x);

	inline ClickType operator++(ClickType& x) { return x = (ClickType)(std::underlying_type<ClickType>::type(x) + 1); };
	ClickType operator*(ClickType c);
	ClickType begin(ClickType x);
	ClickType end(ClickType x);

}

#endif /* SOURCE_METRONOME_CLICKTYPES_H_ */
