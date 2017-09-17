/*
 * KitsManager.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KITMANAGER_H_
#define SOURCE_DRUMKIT_KITS_KITMANAGER_H_


#include "KitParameters.h"

#include "../../Sound/InstrumentSoundType.h"

#include <vector>
#include <string>


namespace DrumKit
{

	class KitManager
	{

	public:

		explicit KitManager(const std::string& kitsPath);
		virtual ~KitManager();

		static void LoadKit(std::string file, KitParameters& parameters);
		static void SaveKit(std::string file, KitParameters parameters);

		bool DeleteKit(const int& id);
		void ReScan() { ScanFolder(); }

		int GetNumKits() { return int(this->filesPaths.size()); }
		std::vector<std::string> GetKitsLocations() const { return filesPaths; }

	private:

		static Sound::InstrumentSoundType GetSoundType(std::string type);
		static std::string GetSoundTypeStr(Sound::InstrumentSoundType soundType);

		void ScanFolder();

		std::string kitsPath;
		std::vector<std::string> filesPaths;


	};


}

#endif /* SOURCE_DRUMKIT_KITS_KITMANAGER_H_ */
