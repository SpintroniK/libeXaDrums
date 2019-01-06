/*
 * Curves.h
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_

#include "../../../Util/Enums.h"
#include <sstream>
#include <string>
#include <type_traits>


namespace DrumKit
{

	enum class CurveType
	{
		Linear,
		Exponential1,
		Exponential2,
		Log1,
		Log2,
		Loud1,
		Loud2,
		Spline,

		First = Linear,
		Last = Spline
	};


	inline std::ostream& operator<<(std::ostream& o, const CurveType& x)
	{

		std::string os;

		switch (x)
		{

		case CurveType::Exponential1:	os = "Exponential1";break;
		case CurveType::Linear:			os = "Linear";		break;
		case CurveType::Exponential2: 	os = "Exponential2";break;
		case CurveType::Log1: 			os = "Log1";			break;
		case CurveType::Log2: 			os = "Log2";		break;
		case CurveType::Loud1: 			os = "Loud1";		break;
		case CurveType::Loud2: 			os = "Loud2";		break;
		case CurveType::Spline: 		os = "Spline";		break;


		default: break;

		}

		return o << os;
	}


	inline CurveType operator++(CurveType& x) { return x = (CurveType)(std::underlying_type_t<CurveType>(x) + 1); };
	inline CurveType operator*(CurveType x) { return x; };
	inline CurveType begin(CurveType x) { return CurveType::First; };
	inline CurveType end(CurveType x) { CurveType l = CurveType::Last; return ++l; };


	inline std::istream& operator>>(std::istream& is, CurveType& x)
	{
		return Util::StreamToEnum(is, x);
	}
}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVE_H_ */
