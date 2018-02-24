/*
 * Recorder.h
 *
 *  Created on: 24 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_
#define SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_

#include "../../Util/SimpleSafeQueue.h"

#include <tuple>
#include <atomic>
#include <thread>
#include <fstream>
#include <queue>
#include <functional>
#include <string>

namespace DrumKit
{

	class Module;

	class Recorder
	{
	public:

		Recorder();
		virtual ~Recorder();

		void SetDirectory(const std::string& dir) { directory = dir + "Rec/"; }

		template <typename T>
		void SetMetronomeTimeFunc(T&& f)
		{
			getLastClickTime = std::move(std::function<int64_t()>{f});
		}

		void Start();
		void Stop();

		bool Push(std::tuple<int, float, int64_t>&& value) { return recordQueue.Push(value); }
		bool IsRecording(std::memory_order memOrder = std::memory_order_acquire) const { return isRecord.load(memOrder); }

	private:

		void Record();
		void DumpBufferToFile();

		std::function<int64_t()> getLastClickTime;

		std::atomic<bool> isRecord;
		std::string directory;
		std::ofstream file;
		std::thread recordThread;
		std::queue<std::tuple<int, float, int64_t>> buffer;
		Util::SimpleSafeQueue<std::tuple<int, float, int64_t>> recordQueue;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_ */
