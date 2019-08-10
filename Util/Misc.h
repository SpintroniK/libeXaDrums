/*
 * Misc.h
 *
 *  Created on: 11 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_MISC_H_
#define SOURCE_UTIL_MISC_H_

#include <functional>
#include <sstream>
#include <numeric>
#include <utility>
#include <vector>

namespace Util
{

	template <size_t I = 0, typename F, typename... T>
	inline typename std::enable_if_t<I == sizeof...(T)> for_each_tuple(std::tuple<T...>&, F)
	{
		return;
	}

	template <size_t I = 0, typename F, typename... T>
	inline typename std::enable_if_t<(I < sizeof...(T))> for_each_tuple(std::tuple<T...>& t, F f)
	{
		f(std::get<I>(t));
		for_each_tuple<I + 1, F, T...>(t, f);
	}

	template <class T>
	inline void StrToValue(const std::string& is, T& val)
	{
		std::stringstream s(is);
		s >> val;
	}

	template <typename... T>
	inline void VectorOfStrToTuple(const std::vector<std::string>& vec, std::tuple<T...>& tuple)
	{
		size_t i = 0;
		for_each_tuple(tuple, [&](auto& t){ StrToValue(vec[i++], t); });
	}

	/**
	 * Converts every element of input and concatenates the results to a string, where elements are separated by separator.
	 * The last separator is removed.
	 * @param input
	 * @param separator
	 * @return
	 */
	template <typename T>
	static std::string JoinToStr(const T& input, std::string separator = ",")
	{
		std::string str = std::accumulate(std::begin(input), std::end(input), std::string{}, [&](const auto& a, const auto& b) { return a + std::to_string(b) + separator; });
		return str.substr(0, str.size() - separator.size());
	}


	/**
	 *
	 * @brief If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v. Uses comp to compare the values.
	 * @param v the value to clamp.
	 * @param lo the low boundary to clamp v to.
	 * @param hi the high boundary to clamp v to.
	 * @param comp Comparison function object.
	 * @return Clamped value.
	 */
	template <class T, class Compare>
	inline constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp )
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
	template <class T>
	inline constexpr const T& clamp( const T& v, const T& lo, const T& hi )
	{
		return Util::clamp( v, lo, hi, std::less<>() );
	}


}

#endif /* SOURCE_UTIL_MISC_H_ */
