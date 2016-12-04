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
#include <memory>

namespace eXaDrumsApi
{

	class KitCreator
	{

	public:

		KitCreator(const char* dataLocation);
		virtual ~KitCreator();

		// Kit
		void CreateNewKit() { controller.CreateNewKit(); }
		void CreateFromModel(const char* loc) { controller.CreateFromModel(std::string(loc)); }
		int GetNumInstruments() const { return controller.GetNumInstruments(); }
		void SetKitName(const char* name) { controller.SetKitName(std::string(name)); }
		void SaveKit(const char* file) const { controller.SaveKit(std::string(file)); }


		// Instrument
		void CreateNewInstrument() { controller.CreateNewInstrument(); }
		void AddInstrumentToKit() { controller.AddInstrumentToKit(); }
		void SetInstrumentName(const char* name) { controller.SetInstrumentName(std::string(name)); }
		void SetInstrumentType(const char* type) { controller.SetInstrumentType(std::string(type)); }
		void SetInstrumentVolume(const float volume) { controller.SetInstrumentVolume(volume); }
		void AddInstrumentSound(const char* file, const char* type) { controller.AddInstrumentSound(std::string(file), std::string(type)); }
		void AddInstrumentTrigger(const int id, const char* location) { controller.AddInstrumentTrigger(id, std::string(location)); }


		// Util
		int GetNumSounds(const char* type) const { return controller.GetNumSounds(type); }
		void GetSoundTypeById(const char* type, int id, char* soundType, int& length) const;
		int GetNumTriggers(const char* type) const { return controller.GetNumTriggers(type); }
		void GetTriggerTypeById(const char* type, int id, char* triggerType, int& length) const;
		int GetNumInstrumentTypes() const { return controller.GetNumInstrumentTypes(); }
		void GetInstrumentTypeById(int id,  char* name, int& length) const;


	private:

		DrumKit::KitCreator& controller;

	};

} /* namespace eXaDrumsApi */

#endif /* SOURCE_API_KITCREATOR_API_H_ */
