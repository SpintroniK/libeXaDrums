/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_
#define LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_

/* The relative path helps when builddir differs from srcdir */
#include "../Api/Version.h"
#include "../Util/ErrorHandling.h"

#include <string>
#include <vector>
#include <memory>
#include <atomic>

#include <cmath>

namespace DrumKit { class Module; class Metronome; }
namespace Sound { class Alsa; class Mixer;}

namespace eXaDrumsApi
{

	class eXaDrums
	{

		friend class Config;

	public:

		explicit eXaDrums(const char* dataLocation) noexcept;
		virtual ~eXaDrums();

		// eXaDrums
		bool IsStarted() const noexcept { return isStarted.load(); }
		std::string GetDataLocation() const noexcept;

		// Module
		void Start();
		void Stop();
		void EnableRecording(bool enable);
		void RecorderExport(const std::string& fileName);

		// Metronome
		void EnableMetronome(bool enable) const;
		void RestartMetronome() const;
		void ChangeTempo(std::size_t tempo) const;
		void ChangeVolume(std::size_t volume) const;
		std::size_t GetTempo() const noexcept;
		std::size_t GetClickVolume() const noexcept;
		void SaveMetronomeConfig() const;
		double GetClickPosition() const noexcept;
		long long GetLastClickTime() const noexcept;

		std::vector<std::string> GetClicksTypes();
		void SetClickType(std::size_t id);
		std::size_t GetClickTypeId() const;

		std::vector<int> GetRhythms() const;
		std::size_t GetRhythm() const noexcept;
		void SetRhythm(std::size_t rhythm) noexcept;

		std::vector<int> GetBpms() const;
		std::size_t GetBpmeas() const noexcept;
		void SetBpmeas(std::size_t bpmeas) noexcept;


		// Kits
		void SelectKit(std::size_t id);
		void SaveKitConfig(std::size_t id) const;
		void DeleteKit(std::size_t id);
		void ReloadKits();
		std::size_t GetNumKits() const noexcept;
		std::string GetKitDataFileName();
		std::vector<std::string> GetKitsNames();

		// Instruments
		void SetInstrumentVolume(std::size_t id, std::size_t volume);
		std::size_t GetInstrumentVolume(std::size_t id) const;
		std::vector<std::string> GetInstrumentsNames();
		std::vector<int> GetInstrumentTriggersIds(std::size_t instrumentId) const;

		// Triggers
		long long GetLastTrigTime() const noexcept;
		std::size_t GetLastTrigValue() const noexcept;
		void SetTriggerSensorValue(std::size_t id, char channel, short data);

		// Sensors
		std::size_t GetSensorsResolution() const noexcept;
		bool IsSensorVirtual() const noexcept;
		bool IsSensorSpi() const noexcept;

		// Sound
		std::string GetAudioDeviceName() const noexcept;

		Util::error GetInitError() const { return this->init_error; }

	private:

		Util::error Start_();
		Util::error Stop_();
		Util::error EnableRecording_(bool enable);
		Util::error SelectKit_(int id);
		Util::error DeleteKit_(int id);
		Util::error SaveKitConfig_(std::size_t id) const;
		Util::error SetInstrumentVolume_(std::size_t id, std::size_t volume);

		const char* GetDataLocation_() const noexcept;
		const char* GetKitDataFileName_();
		void GetClicksTypes_(const char** data, unsigned int& size);
		void GetRhythms_(int* data, unsigned int& size) const;
		void GetBpms_(int* data, unsigned int& size) const;
		void GetKitsNames_(const char** data, unsigned int& size);
		void GetInstrumentsNames_(const char** data, unsigned int& size);
		Util::error RecorderExport_(const char* fileName);
		void GetInstrumentTriggersIds_(int instrumentId, int* data, unsigned int& size) const;


		static const std::string metronomeConfigFile;
		static const std::string alsaConfigFile;

		std::string dataLocation;
		std::string kitDataFileName;

		std::unique_ptr<DrumKit::Module> drumModule;

		std::unique_ptr<Sound::Alsa> alsa;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<DrumKit::Metronome> metronome;

		std::atomic<bool> isStarted;

		// Local copies of all the enums
		std::vector<std::string> clicksTypes;
		std::vector<std::string> kitsNames;
		std::vector<std::string> instrumentsNames;

		Util::error init_error;

	};
}

#include "eXaDrums.hpp"

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
