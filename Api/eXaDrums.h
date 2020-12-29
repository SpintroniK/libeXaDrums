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

		/**
		 * @brief Construct a new eXaDrums object
		 * 
		 * @param dataLocation Path to the configuration files
		 */
		explicit eXaDrums(const char* dataLocation) noexcept;

		/**
		 * @brief Destroy the eXaDrums object
		 * 
		 */
		virtual ~eXaDrums();

		// eXaDrums
		/**
		 * @brief Return the current state of the module (playing/stopped)
		 * 
		 * @return true The module is currently running
		 * @return false The module is stopped
		 */
		bool IsStarted() const noexcept { return isStarted.load(); }

		/**
		 * @brief Get the Data folder location
		 * 
		 * @return std::string Data folder path
		 */
		std::string GetDataLocation() const noexcept;

		/**
		 * @brief Get the current version of libexadrums
		 * 
		 * @return std::string Version as string, e.g.: "x.y.z"
		 */
		static std::string GetVersion() noexcept;

		// Module

		/**
		 * @brief Start the drum module
		 * 
		 */
		void Start();

		/**
		 * @brief Stop the drum module
		 * 
		 */
		void Stop();

		/**
		 * @brief Enable or disable beat recording
		 * 
		 * @param enable Enable recording true, disable recording if false
		 */
		void EnableRecording(bool enable);

		/**
		 * @brief Export raw beats data to xml format
		 * 
		 * @param fileName The xml output file name
		 */
		void RecorderExport(const std::string& fileName);

		/**
		 * @brief Export recorded data to wav (PCM)
		 * 
		 * @param fileName The wav output file name
		 */
		void RecorderExportPCM(const std::string& fileName);

		/**
		 * @brief Purge recorder temporary (csv) file
		 * 
		 */
		void RecorderPurgeTempFile();

		// Metronome
		
		/**
		 * @brief Enable or disable metronome
		 * 
		 * @param enable Enable metronome if true, disable it if false
		 */
		void EnableMetronome(bool enable) const;

		/**
		 * @brief Restart the metrnome
		 * 
		 */
		void RestartMetronome() const;

		/**
		 * @brief Set metronome tempo
		 * 
		 * @param tempo Int value: 40 to 250 bpm 
		 */
		void ChangeTempo(std::size_t tempo) const;

		/**
		 * @brief Set metronome volume
		 * 
		 * @param volume Int value from 0 to 100
		 */
		void ChangeClickVolume(std::size_t volume) const;

		/**
		 * @brief Get the current tempo
		 * 
		 * @return std::size_t current tempo
		 */
		std::size_t GetTempo() const noexcept;

		/**
		 * @brief Get the click olume
		 * 
		 * @return std::size_t click volume from 0 to 100
		 */
		std::size_t GetClickVolume() const noexcept;

		/**
		 * @brief Save the current metronome configuration
		 * 
		 */
		void SaveMetronomeConfig() const;

		/**
		 * @brief Get the relative click position in the current measure
		 * 
		 * @return double relative click position from 0 to 1
		 */
		double GetClickPosition() const noexcept;

		/**
		 * @brief Get the last time a new measure started
		 * 
		 * @return long long timestamp
		 */
		long long GetLastClickTime() const noexcept;

		/**
		 * @brief Get the clicks types
		 * 
		 * @return std::vector<std::string> clicks types names
		 */
		std::vector<std::string> GetClicksTypes();

		/**
		 * @brief Set the click type
		 * 
		 * @param id click type index
		 */
		void SetClickType(std::size_t id);

		/**
		 * @brief Get the click type index
		 * 
		 * @return std::size_t click type index
		 */
		std::size_t GetClickTypeId() const;

		/**
		 * @brief Get the rhythms list
		 * 
		 * @return std::vector<int> Rythms: 
		 */
		std::vector<int> GetRhythms() const;

		/**
		 * @brief Get the current metronome rhythm
		 * 
		 * @return std::size_t Rhythm value
		 */
		std::size_t GetRhythm() const noexcept;

		/**
		 * @brief Set the metronome rhythm (metronome plays 'rhythm' times faster)
		 * 
		 * @param rhythm Rhythm value
		 */
		void SetRhythm(std::size_t rhythm) noexcept;

		/**
		 * @brief Get the list of available number of clicks per measure
		 * 
		 * @return std::vector<int> List of values from 1 to 8 (number of metronome clicks per measure)
		 */
		std::vector<int> GetBpms() const;

		/**
		 * @brief Get the number of beats to be played by the metronome, per measure
		 * 
		 * @return std::size_t number of beats per measure
		 */
		std::size_t GetBpmeas() const noexcept;

		/**
		 * @brief Set the number of beats to be played by the metronome, per measure
		 * 
		 * @param bpmeas number of beats per measure
		 */
		void SetBpmeas(std::size_t bpmeas) noexcept;


		// Kits

		/**
		 * @brief Select drum kit to play with
		 * 
		 * @param id Drum kit id
		 */
		void SelectKit(std::size_t id);

		/**
		 * @brief Save drum kit configuration
		 * 
		 * @param id Drum kit id
		 */
		void SaveKitConfig(std::size_t id) const;

		/**
		 * @brief Delete drum kit
		 * 
		 * @param id Drum kit id
		 */
		void DeleteKit(std::size_t id);

		/**
		 * @brief Reload all drum kits configuration (from file)
		 * 
		 */
		void ReloadKits();

		/**
		 * @brief Get the number of drum kits
		 * 
		 * @return std::size_t The number of drum kits
		 */
		std::size_t GetNumKits() const noexcept;

		/**
		 * @brief Get the kit data file name
		 * 
		 * @return std::string file name
		 */
		std::string GetKitDataFileName();

		/**
		 * @brief Get the drum kits names
		 * 
		 * @return std::vector<std::string> Drum kits names
		 */
		std::vector<std::string> GetKitsNames();

		// Instruments
		/**
		 * @brief Set an Instrument volume
		 * 
		 * @param id Instrument id
		 * @param volume Volume (0, 100)
		 */
		void SetInstrumentVolume(std::size_t id, std::size_t volume);

		/**
		 * @brief Get an Instrument volume
		 * 
		 * @param id Instrument id
		 * @return std::size_t Instrument volume (0, 100)
		 */
		std::size_t GetInstrumentVolume(std::size_t id) const;

		/**
		 * @brief Get the instruments names
		 * 
		 * @return std::vector<std::string> List of instruments names 
		 */
		std::vector<std::string> GetInstrumentsNames();

		/**
		 * @brief Get an instrument triggers ids
		 * 
		 * @param instrumentId instrument id
		 * @return std::vector<int> List of triggers ids
		 */
		std::vector<int> GetInstrumentTriggersIds(std::size_t instrumentId) const;

		// Triggers

		/**
		 * @brief Get the last trig timestamp
		 * 
		 * @return long long Timestamp of the last trig event
		 */
		long long GetLastTrigTime() const noexcept;

		/**
		 * @brief Get the last trig value
		 * 
		 * @return std::size_t Get last trig event's velocity
		 */
		std::size_t GetLastTrigValue() const noexcept;

		/**
		 * @brief Get the Trigger value
		 * 
		 * @param id Trigger index
		 * @return float Last trigger value
		 */
		float GetTriggerValue(size_t id);

		/**
		 * @brief Set a given trigger sensor's value
		 * 
		 * @param id Trigger id
		 * @param channel Trigger channel
		 * @param data Trig event's intensity
		 */
		void SetTriggerSensorValue(std::size_t id, char channel, short data);

		// Sensors

		/**
		 * @brief Get the sensors resolution
		 * 
		 * @return std::size_t Sensors resolution in bits
		 */
		std::size_t GetSensorsResolution() const noexcept;

		/**
		 * @brief Get the sensor type (virtual or internal)
		 * 
		 * @return true If the sensor is virtual
		 * @return false If the sensor is internal
		 */
		bool IsSensorVirtual() const noexcept;

		/**
		 * @brief Get the sensor's data transfer protocol (SPI of not)
		 * 
		 * @return true If the sensor uses SPI
		 * @return false If the sensor doesn't use SPI
		 */
		bool IsSensorSpi() const noexcept;

		// Sound

		/**
		 * @brief Get the audio device name
		 * 
		 * @return std::string Audio device name
		 */
		std::string GetAudioDeviceName() const noexcept;

		/**
		 * @brief Get the init error
		 * 
		 * @return Util::error Error struct (state and message)
		 */
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
		static const char* GetVersion_() noexcept;
		const char* GetKitDataFileName_();
		void GetClicksTypes_(const char** data, unsigned int& size);
		void GetRhythms_(int* data, unsigned int& size) const;
		void GetBpms_(int* data, unsigned int& size) const;
		void GetKitsNames_(const char** data, unsigned int& size);
		void GetInstrumentsNames_(const char** data, unsigned int& size);
		Util::error RecorderExport_(const char* fileName);
		Util::error RecorderExportPCM_(const char* fileName);
		Util::error RecorderPurgeTempFile_();
		void GetInstrumentTriggersIds_(int instrumentId, int* data, unsigned int& size) const;
		Util::error GetTriggerValue_(size_t id, float& value);


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
