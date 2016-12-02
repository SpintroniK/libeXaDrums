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
		void SetKitName(const std::string& name) { parameters.kitName = name; };
		void SaveKit(const std::string& file) const;

		// Instruments
		void CreateNewInstrument();
		void AddInstrumentToKit();
		void SetInstrumentName(const std::string name) { this->instrument.instrumentName = name; }
		void SetInstrumentType(const std::string& type);
		void SetInstrumentVolume(const float v) { this->instrument.volume = v; }
		void AddInstrumentSound(const std::string& file, const std::string& type);
		void AddInstrumentTrigger(const int id, const std::string& location);

		// Util
		int GetNumSounds(const std::string& instrumentType) const;
		int GetNumTriggers(const std::string& instrumentType) const;
		int GetNumInstrumentTypes() const { return (int) Util::Enums::GetInstrumentTypes().size(); }
		std::string GetInstrumentTypeById(int id) const;


	private:

		void Test();

		std::string kitsDirectory;
		KitParameters parameters;
		InstrumentParameters instrument;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KITCREATOR_H_ */
