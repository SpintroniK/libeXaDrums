/*
 * ClickTypes.cpp
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */


#include "ClickTypes.h"


namespace DrumKit
{

	std::ostream& operator<<(std::ostream& o, const clickType& x)
	{

		std::string os;

		switch (x)
		{

		case clickType::Sine: 		os = "Sine"; 	break;
		case clickType::Square: 	os = "Square"; 	break;
		default: break;

		}

		return o << os;
	}

	clickType operator*(clickType c) { return c; };
	clickType begin(clickType x) { return clickType::First; };
	clickType end(clickType x) { clickType l = clickType::Last; return ++l; };


}


