/*
 * Serial.h
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_IO_SERIAL_H_
#define SOURCE_IO_SERIAL_H_

#include "Sensor.h"

#include <string>

#include <stdio.h>      // Standard input / output functions
#include <stdlib.h>
#include <string.h>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

namespace IO
{

	class Serial : public Sensor
	{

	public:

		Serial();
		virtual ~Serial();

		void Open();
		void Close();
		virtual short Read(char port);

	private:

		void Configure();

		bool isOpen;

		const unsigned int defaultBaudRate = 230400;
		const std::string defaultPort = "/dev/ttyUSB0";

		unsigned int baudRate;
		std::string port;

		int handle;

		char buf;

	};


}

#endif /* SOURCE_IO_SERIAL_H_ */
