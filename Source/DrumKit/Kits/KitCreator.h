/*
 * KitCreator.h
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITCREATOR_H_
#define SOURCE_DRUMKIT_KITS_KITCREATOR_H_

#include "../../Util/Enums.h"

#include "KitParameters.h"
#include "KitManager.h"

#include <string>
#include <utility>

namespace DrumKit
{

	class KitCreator
	{

	public:

		KitCreator(const std::string& dataLoc);
		virtual ~KitCreator();

		// Kit
		void CreateNewKit();
		void CreateFromModel(const std::string& file);
		int GetNumInstruments() const { return (int)this->parameters.instrumentParameters.size(); }
		void SetKitName(const std::string& name) { parameters.kitName = name; };
		void SaveKit(const std::string& file, bool fullPath = false) const;
		void SaveKit() const;

		// Instruments
		void CreateNewInstrument();
		void AddInstrumentToKit();
		void SetInstrumentName(const std::string name) { this->instrument.instrumentName = name; }
		void SetInstrumentType(const std::string& type);
		void SetInstrumentVolume(const float v) { this->instrument.volume = v; }
		void AddInstrumentSound(const std::string& file, const std::string& type);
		void AddInstrumentTrigger(const int id, const std::string& location);

		void SetInstrumentName(int id, std::string name) { this->parameters.instrumentParameters[id].instrumentName = name; }
		void SetInstrumentTriggersIdsAndLocs(int id, const std::vector<std::pair<int, std::string>>& trigsIdsAndLocs);
		void SetInstrumentSoundsTypesAndLocs(int id, const std::vector<std::pair<std::string, std::string>>& sndsTypesAndLocs);

		std::string GetInstrumentType(int i) const;
		std::vector<int> GetInstrumentsTriggersIds(int i) const;
		std::vector<std::string> GetInstrumentTriggersLocations(int i) const;
		std::vector<std::string> GetInstrumentSoundsTypes(int i) const;
		std::vector<std::string> GetInstrumentSoundsLocs(int i) const;

		// Enums
		// Instruments
		std::vector<std::string> GetInstrumentsTypes() const;
		std::vector<std::string> GetInstrumentsNames() const;

		// Triggers
		std::vector<int> GetTriggersIds() const { return triggersIds; }
		std::vector<std::string> GetTriggersLocations(const std::string& instrumentType) const;

		// Sounds
		std::vector<std::string> GetSoundFiles() const { return soundFiles; }
		std::vector<std::string> GetSoundTypes(const std::string& instrumentType) const;


	private:

		void Test();

		std::string kitsDirectory;
		KitParameters parameters;
		InstrumentParameters instrument;

		std::vector<int> triggersIds;
		std::vector<std::string> soundFiles;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KITCREATOR_H_ */
