/*
 * Sensor.h
 *
 *  Created on: 25 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_IO_ISENSOR_H_
#define LIBEXADRUMS_SOURCE_IO_ISENSOR_H_

namespace IO
{

	class ISensor
	{

	public:

		virtual short GetData(char channel) = 0;

		virtual ~ISensor() {};

	};

} /* namespace IO */

#endif /* LIBEXADRUMS_SOURCE_IO_ISENSOR_H_ */
