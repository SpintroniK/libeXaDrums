/*
 * Accelerometer.cpp
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */


#include "SpiDevices/SpiDev.h"
#include "SpiSensor.h"


namespace IO
{

	// Initilize number of instances
	//std::size_t SpiSensor::numInstances = 0;

	SpiSensor::SpiSensor(const SpiDev* const d, size_t chan) : dev{d}
	{
		this->channel = chan;
		return;
	}

	short SpiSensor::GetData() noexcept
	{
		return dev->ReadChannel(this->channel);
	}

}


