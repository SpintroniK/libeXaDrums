/*
 * SensorsConfig.h
 *
 *  Created on: 21 Feb 2017
 *      Author: jeremy
 */

#ifndef SOURCE_IO_SENSORSCONFIG_H_
#define SOURCE_IO_SENSORSCONFIG_H_

#include "SensorType.h"


namespace IO
{


	struct SensorsConfig
	{

		int samplingRate;
		int resolution;
		SensorType sensorType;

	};


}



#endif /* SOURCE_IO_SENSORSCONFIG_H_ */
