/*
 * Serial.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "Serial.h"

#include <cstdio>      // Standard input / output functions
#include <cstdlib>
#include <cstring>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <cerrno>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

namespace IO
{

	Serial::Serial()
	: isOpen(false),
	  baudRate(230400),
	  port("/dev/ttyUSB0"),
	  handle(),
	  buf()
	{

		this->Open();

		return;
	}

	Serial::~Serial()
	{

		if(isOpen)
			this->Close();

		return;
	}



	short Serial::GetData(char port)
	{

		if(::write(this->handle, &port, 1) == 1)
		{
			auto res = ::read(this->handle, &this->buf, 1);

			if(res != -1)
			{
				if(this->buf == 's')
				{
					auto resValue = ::read(this->handle, &this->buf, 1);
					if(resValue < 0)
					{
						return 0;
					}
				}
			}
		}
		else
			return 0;

		return short(this->buf);
	}

	// PRIVATE

	void Serial::Open()
	{

		this->handle = ::open(this->port.c_str(), O_RDWR| O_NOCTTY);
		this->isOpen = true;

		this->Configure();

		return;
	}

	void Serial::Close()
	{

		if(this->handle)
			::close(this->handle);

		this->isOpen = false;

		return;
	}

	void Serial::Configure()
	{

		if(!isOpen)
			return;

		struct termios tty;
		struct termios tty_old;
		memset(&tty, 0, sizeof tty);

		/* Error Handling */
		if(tcgetattr(this->handle, &tty) != 0 )
		{
		   //std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		}

		/* Save old tty parameters */
		tty_old = tty;

		/* Set Baud Rate */
		cfsetospeed (&tty, (speed_t)B230400);
		cfsetispeed (&tty, (speed_t)B230400);

		/* Setting other Port Stuff */
		tty.c_cflag &= 	~PARENB;            // Make 8n1
		tty.c_cflag &= 	~CSTOPB;
		tty.c_cflag &= 	~CSIZE;
		tty.c_cflag |= 	CS8;

		tty.c_cflag &= 	~CRTSCTS;           // no flow control
		tty.c_cc[VMIN] = 1;                  // read doesn't block
		tty.c_cc[VTIME] = 5;                  // 0.5 seconds read timeout
		tty.c_cflag |=	CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

		/* Make raw */
		cfmakeraw(&tty);

		/* Flush Port, then applies attributes */
		tcflush(this->handle, TCIFLUSH);
		if(tcsetattr (this->handle, TCSANOW, &tty) != 0)
		{
		   //std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		}


		return;
	}

}
