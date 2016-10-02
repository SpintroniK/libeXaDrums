/*
 * KitsManager.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITMANAGER_H_
#define SOURCE_DRUMKIT_KITS_KITMANAGER_H_

#include "../../Util/Enums.h"
#include "../../Sound/InstrumentSoundType.h"

#include "../Instruments/InstrumentType.h"
#include "../Instruments/InstrumentSoundInfo.h"
#include "../Triggers/TriggerLocation.h"

#include "KitParameters.h"

#include <tinyxml2.h>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <cmath>

#include <dirent.h>
#include <unistd.h>

using namespace Sound;

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

		static InstrumentSoundType GetSoundType(std::string type);
		static std::string GetSoundTypeStr(InstrumentSoundType soundType);

		std::string kitsPath;
		std::vector<std::string> filesPaths;


	};


}

#endif /* SOURCE_DRUMKIT_KITS_KITMANAGER_H_ */
