/*
 * Misc.h
 *
 *  Created on: 11 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_MISC_H_
#define SOURCE_UTIL_MISC_H_

#include <functional>

namespace Util
{

	/**
	 *
	 * @brief If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v. Uses comp to compare the values.
	 * @param v the value to clamp.
	 * @param lo the low boundary to clamp v to.
	 * @param hi the high boundary to clamp v to.
	 * @param comp Comparison function object.
	 * @return Clamped value.
	 */
	template<class T, class Compare>
	constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp )
	{
		return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
	}

	/**
	 * @brief If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v.
	 * @param v the value to clamp.
	 * @param lo the low boundary to clamp v to.
	 * @param hi the high boundary to clamp v to.
	 * @return Clamped value.
	 */
	template<class T>
	constexpr const T& clamp( const T& v, const T& lo, const T& hi )
	{
		return clamp( v, lo, hi, std::less<>() );
	}


}

#endif /* SOURCE_UTIL_MISC_H_ */
