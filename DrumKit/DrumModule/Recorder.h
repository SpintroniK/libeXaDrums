/*
 * Recorder.h
 *
 *  Created on: 24 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_
#define SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_

#include "../../Sound/SoundBank/SoundBank.h"
#include "../../Util/SimpleSafeQueue.h"
#include "../../Sound/Alsa/AlsaParams.h"

#include "TrigSound.h"

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

		Recorder(Sound::SoundBank* sndBankPtr, const Sound::AlsaParams& alsaParams) noexcept;
		virtual ~Recorder();

		void SetDirectory(const std::string& dir) noexcept { directory = dir + "Rec/"; }

		template <typename T>
		void SetMetronomeTimeFunc(T&& f) noexcept
		{
			getLastClickTime = std::function<int64_t()>{f};
		}

		void Start();
		void Stop();
		void PurgeTempFile();
		void Export(const std::string& fileName);
		void ExportPCM(const std::string& fileName);

		bool Push(TrigSound&& value) { return recordQueue.Push(value); }
		bool IsRecording(std::memory_order memOrder = std::memory_order_acquire) const { return isRecord.load(memOrder); }

	private:

		void Record();
		void DumpBufferToFile();
		void ConvertFile(const std::string& file);
		void ConvertToPCM(const std::string& file);

		std::atomic<bool> isRecord;

		Sound::SoundBank* soundBankPtr;
		Sound::AlsaParams alsaParameters;

		std::string directory;
		std::string outputFile;
		std::string lastFile;
		std::function<int64_t()> getLastClickTime = []{return 0;};

		std::ofstream file;

		std::thread recordThread;
		std::queue<TrigSound> buffer;
		Util::SimpleSafeQueue<TrigSound> recordQueue;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_DRUMMODULE_RECORDER_H_ */
