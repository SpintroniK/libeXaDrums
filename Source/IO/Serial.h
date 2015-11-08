/*
 * Serial.h
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_IO_SERIAL_H_
#define SOURCE_IO_SERIAL_H_


#include "ISensor.h"

#include <string>

#include <cstdio>      // Standard input / output functions
#include <cstdlib>
#include <cstring>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <cerrno>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

namespace IO
{

	class Serial : public ISensor
	{

	public:

		Serial();
		virtual ~Serial();
		short GetData(char port) override;

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

#endif /* SOURCE_IO_SERIAL_H_ */
