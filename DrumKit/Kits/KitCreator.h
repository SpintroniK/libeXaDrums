/*
 * KitCreator.h
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITCREATOR_H_
#define SOURCE_DRUMKIT_KITS_KITCREATOR_H_

#include "../../Util/Enums.h"
#include "../Triggers/TriggerManager.h"

#include "KitParameters.h"
#include "KitManager.h"

#include <string>
#include <utility>

namespace DrumKit
{

	class KitCreator
	{

	public:

		explicit KitCreator(const std::string& dataLoc) noexcept;
		virtual ~KitCreator();

		// Kit
		void CreateNewKit() noexcept;
		void CreateFromModel(const std::string& file);
		int GetNumInstruments() const noexcept { return (int)this->parameters.instrumentParameters.size(); }
		void SetKitName(const std::string& name) noexcept { parameters.kitName = name; };
		void SaveKit(const std::string& file, bool fullPath = false) const;
		void SaveKit() const;

		// Instruments
		void CreateNewInstrument() noexcept;
		void RemoveInstrument(std::size_t i) noexcept;
		void RemoveLastInstrument() noexcept;
		void AddInstrumentToKit() noexcept;
		void SetInstrumentName(const std::string& name) { this->instrument.instrumentName = name; }
		void SetInstrumentType(const std::string& type);
		void SetInstrumentVolume(const float v) noexcept { this->instrument.volume = v; }
		void AddInstrumentSound(const std::string& file, const std::string& type);
		void AddInstrumentTrigger(const int id, const std::string& location);

		void SetInstrumentName(int id, const std::string& name) { this->parameters.instrumentParameters[id].instrumentName = name; }
		void SetInstrumentType(int id, const std::string& type) { this->parameters.instrumentParameters[id].instrumentType = Util::Enums::ToElement<InstrumentType>(type); }
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
		std::vector<int> GetTriggersIds() const { return TriggerManager::LoadTriggersIds(dataFolder); }
		std::vector<std::string> GetTriggersLocations(const std::string& instrumentType) const;

		// Sounds
		std::vector<std::string> GetSoundTypes(const std::string& instrumentType) const;


	private:

		std::string dataFolder;
		std::string kitsDirectory;
		KitParameters parameters;
		InstrumentParameters instrument;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KITCREATOR_H_ */
