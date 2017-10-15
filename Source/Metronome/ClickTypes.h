/*
 * clickTypes.h
 *
 *  Created on: 28 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_CLICKTYPES_H_
#define SOURCE_METRONOME_CLICKTYPES_H_

#include <sstream>
#include <string>
#include <type_traits>

namespace DrumKit
{

	enum class ClickType
	{

		Sine,
		Square,

		First = Sine,
		Last = Square

	};


	inline std::ostream& operator<<(std::ostream& o, const ClickType& x)
	{

		std::string os;

		switch (x)
		{

		case ClickType::Sine: 		os = "Sine"; 	break;
		case ClickType::Square: 	os = "Square"; 	break;
		default: break;

		}

		return o << os;
	}


	inline ClickType operator++(ClickType& x) { return x = static_cast<ClickType>(std::underlying_type_t<ClickType>(x) + 1); };
	inline ClickType operator*(ClickType c) { return c; };
	inline ClickType begin(ClickType x) { return ClickType::First; };
	inline ClickType end(ClickType x) { ClickType l = ClickType::Last; return ++l; };

}

#endif /* SOURCE_METRONOME_CLICKTYPES_H_ */
