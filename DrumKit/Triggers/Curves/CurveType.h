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
		Exponential,
		Linear,

		First = Exponential,
		Last = Linear
	};


	inline std::ostream& operator<<(std::ostream& o, const CurveType& x)
	{

		std::string os;

		switch (x)
		{

		case CurveType::Exponential:	os = "Exponential";	break;
		case CurveType::Linear:			os = "Linear";		break;


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
