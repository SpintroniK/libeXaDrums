/*
 * SoundBank.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#include "SoundBank.h"

#include <fstream>
#include <algorithm>

#include <dirent.h>

namespace Sound
{

	SoundBank::SoundBank(std::string dataFolder) : soundBankFolder(dataFolder + "SoundBank/")
	{


		return;
	}

	SoundBank::~SoundBank()
	{

		return;
	}


	int SoundBank::AddSound(std::vector<short>& data)
	{
		return AddSound(data, 1.0f);
	}

	int SoundBank::AddSound(std::vector<short>& data, float volume)
	{

		// Add sound to collection
		std::size_t sId = sounds.size();
		sounds.push_back(Sound(sId, data, volume));

		return sounds.back().GetId();
	}

	void SoundBank::DeleteSound(int id)
	{

		sounds.erase(std::remove_if(sounds.begin(), sounds.end(), [&id](Sound& sound) { return id == sound.GetId(); }));

		return;
	}


	int SoundBank::LoadSound(std::string filename)
	{
		return LoadSound(filename, 1.0f);
	}

	int SoundBank::LoadSound(std::string filename, float volume)
	{


		std::string fileLocation = this->soundBankFolder + filename;

		// Open file
		std::ifstream soundFile(fileLocation);

		// Check file validity
		if(!soundFile.good())
		{
			throw - 1;
		}

		soundFile.seekg (0, std::ios::end);

		// Get file size in bytes
		int fileSize = soundFile.tellg();


		soundFile.seekg(0, std::ios::beg);


		std::vector<short> data;
		data.resize(fileSize);

		int i = 0;
		while(soundFile.read((char*)&data[i], sizeof(short))) i++;

		//unsigned int duration = fileSize*sizeof(char)/sizeof(short);


		// Close file
		soundFile.close();

		// Add sound to collection
		std::size_t sId = sounds.size();
		sounds.push_back(Sound(sId, data, volume));

		return sounds.back().GetId();

	}


	std::vector<std::string> SoundBank::GetSoundFiles(std::string dataFolder)
	{

		std::vector<std::string> paths;

		std::string location = dataFolder + "SoundBank/";

		struct dirent* ent;
		DIR* directory = opendir(location.c_str());

		// Scan directory
		while((ent = readdir(directory)) != NULL)
		{
			// Check if entry is a directory
			if(ent->d_type == DT_DIR)
			{

				// Get directory path
				std::string soundsDirPath = location + std::string(ent->d_name) + "/";
				std::string dirName = std::string(ent->d_name) + "/";

				struct dirent* dir;
				DIR* soundsDir = opendir(soundsDirPath.c_str());

				while((dir = readdir(soundsDir)) != NULL)
				{

					// Get file name and extension
					std::string fileName(dir->d_name);
					std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);

					if(fileExtension == "raw")
					{
						paths.push_back(dirName + fileName);
					}

				}

				closedir(soundsDir);
			}
		}

		closedir(directory);

		return paths;
	}



} /* namespace Sound */
