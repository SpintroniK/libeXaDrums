/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_
#define LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_


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

		eXaDrums(const char* dataLocation);
		virtual ~eXaDrums();

		// eXaDrums
		bool IsStarted() const { return isStarted.load(); }
		std::string GetDataLocation() const;

		// Module
		void Start();
		void Stop();

		// Metronome
		void EnableMetronome(bool enable) const;
		void RestartMetronome() const;
		void ChangeTempo(int tempo) const;
		void ChangeVolume(int volume) const;
		int GetTempo() const;
		int GetClickVolume() const;
		void SaveMetronomeConfig() const;
		double GetClickPosition() const;

		std::vector<std::string> GetClicksTypes();
		void SetClickType(int id);
		int GetClickTypeId() const;

		std::vector<int> GetRhythms() const;
		int GetRhythm() const;
		void SetRhythm(int rhythm);

		std::vector<int> GetBpms() const;
		int GetBpmeas() const;
		void SetBpmeas(int bpmeas);


		// Kits
		void SelectKit(int id);
		void SaveKitConfig(int id) const;
		bool DeleteKit(const int& id);
		void ReloadKits();
		int GetNumKits() const;
		std::string GetKitDataFileName();
		std::vector<std::string> GetKitsNames();

		// Instruments
		void SetInstrumentVolume(int id, int volume);
		int GetInstrumentVolume(int id) const;
		std::vector<std::string> GetInstrumentsNames();

		// Triggers
		unsigned long long GetLastTrigTime() const;
		int GetLastTrigValue() const;

	private:

		const char* GetDataLocation_() const;
		const char* GetKitDataFileName_();
		void GetClicksTypes_(const char** data, unsigned int& size);
		void GetRhythms_(int* data, unsigned int& size) const;
		void GetBpms_(int* data, unsigned int& size) const;
		void GetKitsNames_(const char** data, unsigned int& size);
		void GetInstrumentsNames_(const char** data, unsigned int& size);


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

	};
}

#include "eXaDrums.hpp"

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
