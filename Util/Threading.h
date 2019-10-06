/*
 * Threading.h
 *
 *  Created on: 11 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_THREADING_H_
#define SOURCE_UTIL_THREADING_H_

#include "Misc.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <algorithm>

namespace Util
{


	static constexpr size_t minNbThreads = 3; // Minimum number of threads available to enable threads priority.

	/**
	 * @brief Gives a relative priority to a thread, only if more than minNbThreads threads are available.
	 * @param threadHandle Native handle of the thread object.
	 * @param p Priority in percent: 0 = min, 100 = max.
	 * @param schedType Type of scheduler.
	 */
	template <typename T>
	static void SetThreadPriority(const T& threadHandle, int p, int schedType = SCHED_FIFO)
	{

		if(std::thread::hardware_concurrency() >= minNbThreads)
		{
			p = Util::clamp(p, 0, 100);

			auto maxPriority{sched_get_priority_max(SCHED_FIFO)};
			size_t priority = static_cast<size_t>((p * maxPriority) / 100);

			sched_param sch_params;
			sch_params.sched_priority = priority;

			pthread_setschedparam(threadHandle, schedType, &sch_params);
		}
	}

	class SpinLock
	{

	public:

	    void lock()
	    {
	        while(locked.test_and_set(std::memory_order_acquire)) { ; }
	    }

	    void unlock()
	    {
	        locked.clear(std::memory_order_release);
	    }

	private:

	    std::atomic_flag locked = ATOMIC_FLAG_INIT;
	};

}


#endif /* SOURCE_UTIL_THREADING_H_ */
