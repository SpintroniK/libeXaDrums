/*
 * Timing.h
 *
 *  Created on: 15 Sep 2017
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_TIMING_H_
#define SOURCE_UTIL_TIMING_H_

#include <chrono>

namespace Util
{

	// Very useful to easily benchmark things using lambda functions as parameter
	template <typename T, typename Func>
	static double GetTime(const Func& f)
	{

		auto t_start = std::chrono::high_resolution_clock::now();

		f();

		auto t_end = std::chrono::high_resolution_clock::now();

		auto d = std::chrono::duration<double, std::ratio<T::period::num, T::period::den>>(t_end - t_start);

		return d.count();
	}


}

#endif /* SOURCE_UTIL_TIMING_H_ */
