/*
 * SoundBank.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#include "SoundBank.h"

namespace Sound
{

	SoundBank::SoundBank(std::string dataFolder) : soundBankFolder(dataFolder + "/SoundBank")
	{

		return;
	}

	SoundBank::~SoundBank()
	{

		return;
	}

	int SoundBank::LoadSound(std::string filename)
	{


		std::string fileLocation = this->soundBankFolder + "/" +filename;

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
		sounds.push_back(Sound(sId, data));

		return sounds.back().GetId();

	}

} /* namespace Sound */
