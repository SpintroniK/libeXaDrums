/*
 * Timing.h
 *
 *  Created on: 15 Sep 2017
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_TIME_H_
#define SOURCE_UTIL_TIME_H_

#include <chrono>
#include <string>
#include <ctime>

namespace Util
{

	/**
	 * Converts a timestamp (int64_t for instance) in a string that contains the corresponding date.
	 * @param timestamp
	 * @return
	 */
	template <typename T, typename U = std::chrono::microseconds>
	static std::string TimeStampToStr(T timestamp)
	{
		using namespace std::chrono;

	    auto tp = time_point<high_resolution_clock, U>{U{timestamp}};
	    auto time_t = system_clock::to_time_t(tp);

	    auto result = std::string{std::ctime(&time_t)};
	    result.pop_back();

	    return result;
	}

	/**
	 * Very useful to easily benchmark things using lambda functions as parameter.
	 * @param f Callable to be executed.
	 * @return Execution time in units of T.
	 */
	template <typename T, typename Func>
	static double GetTime(const Func& f)
	{

		using namespace std::chrono;

		auto t_start = high_resolution_clock::now();
		f();
		auto t_end = high_resolution_clock::now();

		auto d = duration<double, std::ratio<T::period::num, T::period::den>>(t_end - t_start);

		return d.count();
	}


}

#endif /* SOURCE_UTIL_TIME_H_ */
