/*
 * KitsManager.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITMANAGER_KITMANAGER_H_
#define SOURCE_DRUMKIT_KITMANAGER_KITMANAGER_H_

#include <vector>
#include <string>

#include <dirent.h>

namespace DrumKit
{

	class KitManager
	{

	public:

		KitManager(std::string kitsPath);
		virtual ~KitManager();

		void GetNumKits(int& N);


	private:

		void ScanFolder();

		std::string kitsPath;
		std::vector<std::string> filesList;

	};

}

#endif /* SOURCE_DRUMKIT_KITMANAGER_KITMANAGER_H_ */
