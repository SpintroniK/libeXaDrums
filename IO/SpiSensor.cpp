/*
 * Accelerometer.cpp
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#include "SpiSensor.h"

#include "Spi.h"

//#include <bcm2835.h>


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

		const size_t nBits = 10;
		const auto mask = (1 << nBits) - 1;
		const uint32_t data = (0b0001'1000 | channel) << (nBits + 2);
		std::array<uint8_t, 3> spiData {static_cast<uint8_t>((data & 0x00'ff'00'00) >> 16), 
										static_cast<uint8_t>((data & 0x00'00'ff'00) >> 8), 
										static_cast<uint8_t>(data  & 0x00'00'00'ff)}; 

		
		dev->dataRW(spiData.data(), spiData.size());

		return ((spiData[1] << 8) | spiData[2]) & mask;
	}

}


