/*
 * SoundBank.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#include "SoundBank.h"

#include "../Util/WavUtil.h"

#include <fstream>
#include <algorithm>
#include <stdexcept>

#include <dirent.h>

namespace Sound
{

	SoundBank::SoundBank(const std::string& dataFolder) noexcept : soundBankFolder(dataFolder + "SoundBank/")
	{


		return;
	}

	SoundBank::~SoundBank()
	{

		return;
	}


	int SoundBank::AddSound(const std::vector<short>& data)
	{
		return AddSound(data, 1.0f);
	}

	int SoundBank::AddSound(const std::vector<short>& data, float volume)
	{

		// Add sound to collection
		std::size_t sId = sounds.size();
		sounds.push_back(Sound(sId, data, volume));

		return sounds.back().GetId();
	}

	int SoundBank::AddSound(Sound&& sound, float volume)
	{
		// Add sound to collection
		sound.id = sounds.size();
		sound.volume.store(volume);
		sounds.push_back(std::move(sound));

		return sounds.back().GetId();
	}

	void SoundBank::DeleteSound(int id)
	{

		auto it = std::remove_if(sounds.begin(), sounds.end(), [&id](Sound& sound) { return id == sound.GetId(); });
		if(it != end(sounds))
		{
			sounds.erase(it);
		}

		return;
	}

	void SoundBank::LoopSound(int id, bool s) 
	{
		if(static_cast<size_t>(id) < sounds.size()) 
		{
			sounds[id].SetLoop(s); 
		}
	}


	int SoundBank::LoadSound(const std::string& filename)
	{
		return LoadSound(filename, 1.0f);
	}

	int SoundBank::LoadSound(const std::string& filename, float volume)
	{


		std::string fileLocation = this->soundBankFolder + filename;

		// Open file
		std::ifstream soundFile(fileLocation);

		// Check file validity
		if(!soundFile.good())
		{
			throw - 1;
		}

		soundFile.seekg(0, std::ios::end);

		// Get file size in bytes
		size_t fileSize = soundFile.tellg();

		soundFile.seekg(0, std::ios::beg);

		// HEADER
		std::vector<uint8_t> header_data(44);
		soundFile.read((char*)header_data.data(), header_data.size());

		WavHeader header(header_data);

		size_t chunkLength = header.get_subchunk2_size();
		size_t dataLength = 0;

		if(chunkLength + header_data.size() == fileSize)
		{
			dataLength = chunkLength;
		}
		else
		{
			std::string error{"Couldn't read sound file: " + fileLocation};
			throw std::runtime_error(error);
		}

		uint32_t data_size_short = dataLength / sizeof(short);
		std::vector<short> data(data_size_short);

		soundFile.read((char*)data.data(), dataLength);

		// Close file
		soundFile.close();

		// Add sound to collection
		std::size_t sId = sounds.size();
		sounds.push_back(Sound(sId, data, volume));

		return sounds.back().GetId();

	}


	std::vector<std::string> SoundBank::GetSoundFiles(const std::string& dataFolder)
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


