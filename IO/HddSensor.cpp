/*
 * Sensor.cpp
 *
 *  Created on: 7 May 2015
 *      Author: jeremy
 */

#include "HddSensor.h"

#include <fstream>
#include <iostream>
#include <ctime>

namespace IO
{


	const std::vector<std::string> HddSensor::dataFiles({"out.raw", "out.raw", "out.raw"});


	HddSensor::HddSensor(const std::string& dataFolder, size_t chan) : path(dataFolder), index(0)
	{
		this->channel = chan;
		return;
	}


	short HddSensor::GetData()
	{

		if(data.empty())
		{
			ReadData();
		}

		// Wait for a few microseconds
		{
			clock_t endwait = clock() + (5.0f * (double)CLOCKS_PER_SEC) / 1000000.0f ;
			while (clock() < endwait);
		}

		short val = data[++index];

		if(index == data.size())
		{
			index = 0;
		}

		return val;
	}

	// Private Methods

	void HddSensor::ReadData()
	{

		std::string fileName = dataFiles[channel % dataFiles.size()];
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
