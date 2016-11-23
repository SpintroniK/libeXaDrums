/*
 * Curves.h
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_

#include <sstream>
#include <string>
#include <type_traits>


namespace DrumKit
{

	enum class CurveType
	{
		exponential,
		linear,

		First = exponential,
		Last = linear
	};


	inline std::ostream& operator<<(std::ostream& o, const CurveType& x)
	{

		std::string os;

		switch (x)
		{

		case CurveType::exponential:	os = "exponential";	break;
		case CurveType::linear:			os = "linear";		break;


		default: break;

		}

		return o << os;
	}


	inline CurveType operator++(CurveType& x) { return x = (CurveType)(std::underlying_type<CurveType>::type(x) + 1); };
	inline CurveType operator*(CurveType x) { return x; };
	inline CurveType begin(CurveType x) { return CurveType::First; };
	inline CurveType end(CurveType x) { CurveType l = CurveType::Last; return ++l; };


}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_ */
