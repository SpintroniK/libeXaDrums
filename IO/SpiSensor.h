/*
 * Accelerometer.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_SENSOR_H_
#define RASPIDRUMS_SOURCE_IO_SENSOR_H_


#include "ISensor.h"

#include <cstdlib>

namespace IO
{

	class SpiSensor : public ISensor
	{

	public:

		SpiSensor();
		virtual ~SpiSensor();

		short GetData(char channel);
		virtual void SetData(char channel, short value) final {}


	private:

		//static std::size_t numInstances;

	};

}



#endif /* RASPIDRUMS_SOURCE_IO_SENSOR_H_ */
