/*
 * Serial.h
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_IO_SERIAL_H_
#define LIBEXADRUMS_SOURCE_IO_SERIAL_H_


#include "ISensor.h"

#include <string>

namespace IO
{

	class Serial : public ISensor
	{

	public:

		Serial();
		virtual ~Serial();

		short GetData(char port);

	private:

		void Configure();
		void Open();
		void Close();

		bool isOpen;

		//const unsigned int defaultBaudRate = 230400;
		//const std::string defaultPort = "/dev/ttyUSB0";

		unsigned int baudRate;
		std::string port;

		int handle;

		char buf;

	};


}

#endif /* LIBEXADRUMS_SOURCE_IO_SERIAL_H_ */
