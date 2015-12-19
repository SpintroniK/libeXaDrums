/*
 * KitsManager.cpp
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#include "KitManager.h"

namespace DrumKit
{

	KitManager::KitManager(std::string kitsPath) : kitsPath(kitsPath)
	{

		this->ScanFolder();

		return;
	}

	KitManager::~KitManager()
	{

		this->filesList.clear();

		return;
	}


	void KitManager::GetNumKits(int& N)
	{

		N = (int) this->filesList.size();

		return;
	}

	// PRIVATE METHODS

	void KitManager::ScanFolder()
	{

		struct dirent *ent;
		DIR* directory = opendir(kitsPath.c_str());

		while((ent = readdir(directory)) != NULL)
		{
			std::string fileName(ent->d_name);
			std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);

			if(fileExtension == "xml")
			{
				this->filesList.push_back(this->kitsPath + fileName);
			}
		}

		return;
	}


} /* namespace DrumKit */
