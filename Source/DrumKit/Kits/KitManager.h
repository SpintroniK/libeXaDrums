/*
 * KitsManager.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITMANAGER_H_
#define SOURCE_DRUMKIT_KITS_KITMANAGER_H_

#include "../../Sound/SoundProcessor/Curves/CurveType.h"
#include "../../Sound/SoundProcessor/InstrumentSoundType.h"

#include "../../IO/SensorType.h"

#include "../Instruments/InstrumentType.h"
#include "../Instruments/InstrumentSoundInfo.h"
#include "../Triggers/TriggerType.h"
#include "../Triggers/TriggerParameters.h"
#include "../Triggers/TriggerLocation.h"

#include "KitParameters.h"

#include <tinyxml2.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include <dirent.h>


namespace DrumKit
{

	class KitManager
	{

	public:

		KitManager(std::string kitsPath);
		virtual ~KitManager();


		void LoadKit(std::string file, KitParameters& parameters);
		void LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams);

		int GetNumKits() { return int(this->filesPaths.size()); }

		std::vector<std::string> GetKitsLocations() const { return filesPaths; }

	private:

		void ScanFolder();

		static TriggerType GetTriggerType(std::string type);
		static TriggerLocation GetTriggerLocation(std::string location);
		static InstrumentType GetInstrumentType(std::string type);
		static Sound::CurveType GetCurveType(std::string type);
		static Sound::InstrumentSoundType GetSoundType(std::string type);

		std::string kitsPath;
		std::vector<std::string> filesPaths;

	};

}

#endif /* SOURCE_DRUMKIT_KITS_KITMANAGER_H_ */
