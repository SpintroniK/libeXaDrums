/*
 * KitCreator.h
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_KITCREATOR_API_H_
#define SOURCE_API_KITCREATOR_API_H_


#include "../DrumKit/Kits/KitCreator.h"

#include <string>
#include <vector>

namespace eXaDrumsApi
{

	class KitCreator
	{

	public:

		KitCreator(const char* dataLocation);
		virtual ~KitCreator();

		// Kit
		void CreateNewKit();
		void CreateFromModel(const char* loc);
		int GetNumInstruments() const;
		void SetKitName(const char* name);
		void SaveKit(const char* file) const;
		void SaveKit() const;


		// Instrument
		void CreateNewInstrument();
		void AddInstrumentToKit();
		void SetInstrumentName(const char* name);
		void SetInstrumentType(const char* type);
		void SetInstrumentVolume(const float volume);
		void AddInstrumentSound(const char* file, const char* type);
		void AddInstrumentTrigger(const int id, const char* location);

		std::string GetInstrumentType(int i);
		std::vector<int> GetInstrumentTriggersIds(int i) const;
		std::vector<std::string> GetInstrumentTriggersLocations(int i);
		std::vector<std::string> GetInstrumentSoundsTypes(int i);
		std::vector<std::string> GetInstrumentSoundsLocs(int i);

		// Enums
		// Instruments
		std::vector<std::string> GetInstrumentsTypes();
		std::vector<std::string> GetInstrumentsNames();

		// Triggers
		std::vector<int> GetTriggersIds() const;
		std::vector<std::string> GetTriggersLocations(const std::string instrumentType);

		// Sounds
		std::vector<std::string> GetSoundsFiles();
		std::vector<std::string> GetSoundsTypes(const std::string instrumentType);


	private:

		const char* GetInstrumentType_(int i);

		void GetInstrumentTriggersIds_(int i, int* data, unsigned int& size) const;
		void GetTriggersIds_(int* data, unsigned int& size) const;

		void GetInstrumentTriggersLocations_(int i, const char** data, unsigned int& size);
		void GetTriggersLocations_(const char* instrumentType, const char** data, unsigned int& size);

		void GetInstrumentSoundsTypes_(int i, const char** data, unsigned int& size);
		void GetSoundTypes_(const char* instrumentType, const char** data, unsigned int& size);

		void GetInstrumentSoundsLocs_(int i, const char** data, unsigned int& size);
		void GetSoundFiles_(const char** data, unsigned int& size);

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
		DrumKit::KitCreator& controller;

	};

} /* namespace eXaDrumsApi */

#include "KitCreator_api.hpp"

#endif /* SOURCE_API_KITCREATOR_API_H_ */
