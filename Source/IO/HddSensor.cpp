/*
 * Sensor.cpp
 *
 *  Created on: 7 May 2015
 *      Author: jeremy
 */

#include "HddSensor.h"

#include <fstream>

namespace IO
{


	const std::vector<std::string> HddSensor::dataFiles({"out.raw", "out.raw", "hihat.raw"});


	HddSensor::HddSensor(const char* dataFolder) : path(dataFolder), index(0)
	{


		return;
	}

	HddSensor::~HddSensor()
	{


		return;
	}


	short HddSensor::GetData(char channel)
	{


		if(data.empty())
		{
			ReadData(channel);
		}

		// Artificial delay (works well in Debug with my laptop...)
		for(int i = 0; i < 2500; i++);

		short val = data[++index];

		if(index == data.size())
		{
			index = 0;
		}

		return val;
	}

	// Private Methods

	void HddSensor::ReadData(char channel)
	{

		std::string fileName = dataFiles[channel];
		std::string fileLoc(path + fileName);

		std::ifstream file(fileLoc, std::ifstream::binary);

		if(!file.good())
		{
			throw - 1;
		}

		short val;

		while(file.read((char*)&val, sizeof(short)))
		{
			data.push_back(val);
		}

		file.close();


		return;
	}

}


