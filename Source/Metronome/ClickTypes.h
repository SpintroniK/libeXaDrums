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

	enum class clickType
	{

		Sine,
		Square,

		First = Sine,
		Last = Square

	};

	std::ostream& operator<<(std::ostream& o, const clickType& x);

	inline clickType operator++(clickType& x) { return x = (clickType)(std::underlying_type<clickType>::type(x) + 1); };
	clickType operator*(clickType c);
	clickType begin(clickType x);
	clickType end(clickType x);

}

#endif /* SOURCE_METRONOME_CLICKTYPES_H_ */
