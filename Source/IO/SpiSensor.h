/*
 * Accelerometer.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_SENSOR_H_
#define RASPIDRUMS_SOURCE_IO_SENSOR_H_

#include "Sensor.h"

#include <bcm2835.h>

#include <iostream>


namespace IO
{

	class SpiSensor : public Sensor
	{

	public:

		SpiSensor();
		virtual ~SpiSensor();

		virtual short GetData(char channel);


	private:

	};



}

#endif /* RASPIDRUMS_SOURCE_IO_SENSOR_H_ */
