/*
 * Recorder.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: jeremy
 */

#include "Recorder.h"

#include <chrono>

namespace DrumKit
{

	Recorder::Recorder() : isRecord{false}
	{

	}

	Recorder::~Recorder()
	{
		isRecord.store(false, std::memory_order_relaxed);

		if(recordThread.joinable())
		{
			recordThread.join();
		}
	}

	void Recorder::Start()
	{
		isRecord.store(true, std::memory_order_release);
		recordThread = std::thread(&Recorder::Record, this);
	}

	void Recorder::Stop()
	{
		isRecord.store(false, std::memory_order_release);
		recordThread.join();
	}

	// PRIVATE Methods


	void Recorder::DumpBufferToFile()
	{
		while(!buffer.empty())
		{
			int soundId;
			float volume;
			int64_t time;
			std::tie(soundId, volume, time) = buffer.front();
			buffer.pop();

			file << soundId << ',' << time << ',' << volume << '\n';
		}

		// Insert keyframe if the metronome is running
		auto lastClickTime = getLastClickTime();

		if(lastClickTime > 0)
		{
			file << -1 << ',' << lastClickTime << ',' << 0.5f << '\n';
		}

		file.flush();
	};

	void Recorder::Record()
	{

		using namespace Util;
		using namespace std::chrono_literals;
		using namespace std::chrono;
		using namespace std::this_thread;

		using TrigSound = std::tuple<int, float, int64_t>;

		// Create new file
		const auto fileTimeStamp = system_clock::now().time_since_epoch().count();
		const std::string fileName = directory + std::to_string(fileTimeStamp) + ".csv";

		file.open(fileName);

		while(isRecord.load(std::memory_order_acquire))
		{

			TrigSound trigSound;

			while(recordQueue.Pop(trigSound))
			{
				buffer.emplace(std::move(trigSound));
			}

			// Write data to file
			if(buffer.size() >= recordQueue.Capacity() / 8)
			{
				DumpBufferToFile();
			}

			// Wait before we try to get more sounds
			if(isRecord.load(std::memory_order_relaxed))
			{
				sleep_for(500ms);
			}

		}

		DumpBufferToFile();

		file.close();
	}

} /* namespace DrumKit */


