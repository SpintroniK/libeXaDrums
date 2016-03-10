/*
 * SoundBank.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#include "SoundBank.h"

namespace Sound
{

	SoundBank::SoundBank()
	{

		return;
	}

	SoundBank::~SoundBank()
	{

		return;
	}

	void SoundBank::LoadSound(std::string filename, std::vector<short>& data, unsigned int& duration)
	{


		//XXX Hack! Needs to be fixed. Get file location
		std::string fileLocation = "../Data/SoundBank/" + filename;

		// Open file
		std::ifstream soundFile(fileLocation);

		// Check file validity
		if(!soundFile.good())
			throw - 1;

		soundFile.seekg (0, std::ios::end);

		// Get file size in bytes
		int fileSize = soundFile.tellg();

		//short* soundData = new short[fileSize];

		soundFile.seekg(0, std::ios::beg);


		data.clear();
		data.resize(fileSize);

		int i = 0;
		while(soundFile.read((char*)&data[i], sizeof(short))) i++;

		duration = fileSize*sizeof(char)/sizeof(short);


		// Close file
		soundFile.close();

		return;
	}

} /* namespace Sound */
