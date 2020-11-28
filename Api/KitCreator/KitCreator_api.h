/*
 * KitCreator.h
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_KITCREATOR_KITCREATOR_API_H_
#define SOURCE_API_KITCREATOR_KITCREATOR_API_H_

#include "../../Util/ErrorHandling.h"
#include "../../DrumKit/Kits/KitCreator.h"

#include <string>
#include <vector>
#include <utility>

namespace eXaDrumsApi
{

	class KitCreator
	{

	public:

		/**
		 * @brief Construct a new Kit Creator.
		 * 
		 * @param dataLocation eXaDrums configuration folder location.
		 */
		explicit KitCreator(const char* dataLocation);

		/**
		 * @brief Destroy the Kit Creator.
		 * 
		 */
		~KitCreator();

		// Kit
		/**
		 * @brief Create a New kit.
		 * 
		 */
		void CreateNewKit() noexcept;

		/**
		 * @brief Create a new kit by copying an existing one.
		 * 
		 * @param loc Existing kit file name.
		 */
		void CreateFromModel(const char* loc);

		/**
		 * @brief Get the number of instruments in the current kit.
		 * 
		 * @return int Number of instruments.
		 */
		int GetNumInstruments() const noexcept;

		/**
		 * @brief Set the kit name.
		 * 
		 * @param name Kit name.
		 */
		void SetKitName(const char* name) noexcept;

		/**
		 * @brief Save current kit to a file.
		 * 
		 * @param file Destination file.
		 */
		void SaveKit(const char* file) const;

		/**
		 * @brief Save current kit configuration. 
		 * 
		 */
		void SaveKit() const;

		// Instrument
		/**
		 * @brief Create a new instrument.
		 * 
		 */
		void CreateNewInstrument() noexcept;

		/**
		 * @brief Remove a given instrument.
		 * 
		 * @param i Instrument index (id).
		 */
		void RemoveInstrument(std::size_t i) noexcept;

		/**
		 * @brief Delete the last instrument.
		 * 
		 */
		void RemoveLastInstrument() noexcept;

		/**
		 * @brief Add current instrument to kit.
		 * 
		 */
		void AddInstrumentToKit() noexcept;

		/**
		 * @brief Set the current instrument name.
		 * 
		 * @param name Instrument name.
		 */
		void SetInstrumentName(const char* name);

		/**
		 * @brief Set the current instrument type.
		 * 
		 * @param type Instrument type name.
		 */
		void SetInstrumentType(const char* type);

		/**
		 * @brief Set the current instrument volume.
		 * 
		 * @param volume Instrument volume (from 0 to 1).
		 */
		void SetInstrumentVolume(const float volume) noexcept;

		/**
		 * @brief Add sound to current instrument.
		 * 
		 * @param file Sound file location.
		 * @param type Sound type.
		 */
		void AddInstrumentSound(const char* file, const char* type);

		/**
		 * @brief Add trigger to current instrument.
		 * 
		 * @param id Trigger id.
		 * @param location Trigger location.
		 */
		void AddInstrumentTrigger(const int id, const char* location);

		/**
		 * @brief Set instrument name.
		 * 
		 * @param id Instrument id.
		 * @param name Instrument name to be set.
		 */
		void SetInstrumentName(int id, const char* name);

		/**
		 * @brief Set instrument type.
		 * 
		 * @param id Instrument id.
		 * @param type Instrument type name.
		 */
		void SetInstrumentType(int id, const char* type);

		/**
		 * @brief Set instrument triggers ids and locations.
		 * 
		 * @param id Instrument id.
		 * @param trigsIdsAndLocs Triggers ids and locations.
		 */
		void SetInstrumentTriggersIdsAndLocs(int id, const std::vector<std::pair<int, std::string>>& trigsIdsAndLocs);

		/**
		 * @brief Set instrument sounds types and locations.
		 * 
		 * @param id Instrument id.
		 * @param sndTypesAndLocs Sounds types and locations.
		 */
		void SetInstrumentSoundsTypesAndLocs(int id, const std::vector<std::pair<std::string, std::string>>& sndTypesAndLocs);


		/**
		 * @brief Get an instrument's type.
		 * 
		 * @param i Instrument id.
		 * @return std::string Instrument type.
		 */
		std::string GetInstrumentType(int i);

		/**
		 * @brief Get instrument triggers ids.
		 * 
		 * @param i Instrument id.
		 * @return std::vector<int> Triggers ids.
		 */
		std::vector<int> GetInstrumentTriggersIds(int i) const;

		/**
		 * @brief Get instrument triggers locations.
		 * 
		 * @param i Instrument id.
		 * @return std::vector<std::string> Triggers locations.
		 */
		std::vector<std::string> GetInstrumentTriggersLocations(int i);

		/**
		 * @brief Get instrument sounds types.
		 * 
		 * @param i Instrument id.
		 * @return std::vector<std::string> Sounds types.
		 */
		std::vector<std::string> GetInstrumentSoundsTypes(int i);

		/**
		 * @brief Get instrument sounds locations.
		 * 
		 * @param i Instrument id.
		 * @return std::vector<std::string> Sounds locations.
		 */
		std::vector<std::string> GetInstrumentSoundsLocs(int i);

		// Enums
		// Instruments
		/**
		 * @brief Get the list of instruments types.
		 * 
		 * @return std::vector<std::string> Instruments types.
		 */
		std::vector<std::string> GetInstrumentsTypes();

		/**
		 * @brief Get the list of instruments names.
		 * 
		 * @return std::vector<std::string> Instruments names.
		 */
		std::vector<std::string> GetInstrumentsNames();

		// Triggers
		/**
		 * @brief Get the list of triggers ids.
		 * 
		 * @return std::vector<int> List of triggers ids.
		 */
		std::vector<int> GetTriggersIds() const;

		/**
		 * @brief Get the possible triggers locations for a given instrument type.
		 * 
		 * @param instrumentType Instrument type.
		 * @return std::vector<std::string> List of possible triggers locations.
		 */
		std::vector<std::string> GetTriggersLocations(const std::string& instrumentType);

		// Sounds
		//std::vector<std::string> GetSoundsFiles();
		/**
		 * @brief Get the possible sounds types for a given instrument type.
		 * 
		 * @param instrumentType Instrument type.
		 * @return std::vector<std::string> List of possible sounds types.
		 */
		std::vector<std::string> GetSoundsTypes(const std::string& instrumentType);


	private:

		Util::error CreateFromModel_(const char* loc);
		Util::error SaveKit_(const char* file) const;
		Util::error SaveKit_() const;
		Util::error SetInstrumentName_(const char* name);
		Util::error SetInstrumentName_(int id, const char* name);

		void SetInstrumentTriggersIdsAndLocs_(int id, int* ids, const char** locs, unsigned int size);
		void SetInstrumentSoundsTypesAndLocs_(int id, const char** types, const char** locs, unsigned int size);

		const char* GetInstrumentType_(int i);

		void GetInstrumentTriggersIds_(int i, int* data, unsigned int& size) const;
		void GetTriggersIds_(int* data, unsigned int& size) const;

		void GetInstrumentTriggersLocations_(int i, const char** data, unsigned int& size);
		void GetTriggersLocations_(const char* instrumentType, const char** data, unsigned int& size);

		void GetInstrumentSoundsTypes_(int i, const char** data, unsigned int& size);
		void GetSoundTypes_(const char* instrumentType, const char** data, unsigned int& size);

		void GetInstrumentSoundsLocs_(int i, const char** data, unsigned int& size);
		//void GetSoundFiles_(const char** data, unsigned int& size);

		void GetInstrumentsTypes_(const char** data, unsigned int& size);
		void GetInstrumentsNames_(const char** data, unsigned int& size);

		// Local copies of all the strings
		std::string instrumentType;

		// Local copies of all the enums
		std::vector<std::string> soundsFiles;
		std::vector<std::string> soundsTypes;
		std::vector<std::string> instrumentsTypes;
		std::vector<std::string> triggersLocations;
		std::vector<std::string> instrumentsNames;
		std::vector<std::string> instrumentTriggersLocations;
		std::vector<std::string> instrumentSoundsTypes;
		std::vector<std::string> instrumentSoundsLocs;

		// Controller
		DrumKit::KitCreator controller;

	};

} /* namespace eXaDrumsApi */

#include "KitCreator_api.hpp"

#endif /* SOURCE_API_KITCREATOR_KITCREATOR_API_H_ */
