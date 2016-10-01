/*
 * KitsManager.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITMANAGER_H_
#define SOURCE_DRUMKIT_KITS_KITMANAGER_H_

#include "../../Sound/SoundProcessor/InstrumentSoundType.h"
#include "../../Util/Enums.h"

#include "../Instruments/InstrumentType.h"
#include "../Instruments/InstrumentSoundInfo.h"
#include "../Triggers/TriggerLocation.h"

#include "KitParameters.h"

#include <tinyxml2.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>

#include <cmath>

#include <dirent.h>
#include <unistd.h>


namespace DrumKit
{

	class KitManager
	{

	public:

		KitManager(std::string kitsPath);
		virtual ~KitManager();

		static void LoadKit(std::string file, KitParameters& parameters);
		static void SaveKit(std::string file, KitParameters parameters);
		bool DeleteKit(const int& id);

		int GetNumKits() { return int(this->filesPaths.size()); }

		std::vector<std::string> GetKitsLocations() const { return filesPaths; }

	private:

		void ScanFolder();

		static TriggerLocation GetTriggerLocation(std::string location);
		static std::string GetTriggerLocationStr(TriggerLocation triggerLocation);
		//static std::string GetInstrumentTypeStr(InstrumentType type);
		static Sound::InstrumentSoundType GetSoundType(std::string type);
		static std::string GetSoundTypeStr(Sound::InstrumentSoundType soundType);

		std::string kitsPath;
		std::vector<std::string> filesPaths;

		//static std::map<InstrumentType, std::string> instrumentsTypes;
		static std::map<TriggerLocation, std::string> triggersLocations;
		static std::map<Sound::InstrumentSoundType, std::string> soundsTypes;

	};


}

#endif /* SOURCE_DRUMKIT_KITS_KITMANAGER_H_ */
