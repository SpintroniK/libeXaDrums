/*
 * Sensor.cpp
 *
 *  Created on: 7 May 2015
 *      Author: jeremy
 */

#include "HddSensor.h"

namespace IO
{

	HddSensor::HddSensor(std::string filePath)
	: index(0)
	{

		file = new std::ifstream(filePath, std::ios::in|std::ifstream::binary);

		if(!file->good())
			throw - 1;

		short val;

		while(file->read((char*)&val, sizeof(short)))
			value.push_back(val);

		return;
	}

	HddSensor::~HddSensor()
	{

		file->close();
		delete file;

		return;
	}


	/// PRIVATE

	short HddSensor::GetOutput()
	{

		std::this_thread::sleep_for(std::chrono::microseconds(10));

		short val = value[++index];

		if(index == value.size())
			index = 0;

		return val;
	}

}


