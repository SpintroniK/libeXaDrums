/*
 * Sensor.h
 *
 *  Created on: 25 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_IO_SENSOR_H_
#define SOURCE_IO_SENSOR_H_

namespace IO
{

	class Sensor
	{

	public:

		virtual short GetData(char channel) = 0;

		virtual ~Sensor() {};

	protected:
	private:

	};

} /* namespace IO */

#endif /* SOURCE_IO_SENSOR_H_ */
