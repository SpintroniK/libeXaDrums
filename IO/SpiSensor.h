/*
 * Accelerometer.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_SENSOR_H_
#define RASPIDRUMS_SOURCE_IO_SENSOR_H_


#include "ISensor.h"

#include "SpiDevices/SpiDev.h"

#include <vector>
#include <cstdlib>

namespace IO
{

	class SpiSensor : public ISensor
	{

	public:

		SpiSensor(const SpiDev* const d, size_t channel);
		SpiSensor() = delete;
		virtual ~SpiSensor() = default;

		short GetData() noexcept;
		virtual void SetData(short value) final {}


	private:

		const SpiDev* const dev;

	};

}



#endif /* RASPIDRUMS_SOURCE_IO_SENSOR_H_ */
