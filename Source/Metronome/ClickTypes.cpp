/*
 * ClickTypes.cpp
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */


#include "ClickTypes.h"


namespace DrumKit
{

	std::ostream& operator<<(std::ostream& o, const ClickType& x)
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

	ClickType operator*(ClickType c) { return c; };
	ClickType begin(ClickType x) { return ClickType::First; };
	ClickType end(ClickType x) { ClickType l = ClickType::Last; return ++l; };


}


