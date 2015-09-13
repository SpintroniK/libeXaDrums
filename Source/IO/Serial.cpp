/*
 * Serial.cpp
 *
 *  Created on: 13 Sep 2015
 *      Author: jeremy
 */

#include "Serial.h"

#include <iostream>

namespace IO
{

	Serial::Serial()
	: isOpen(false),
	  baudRate(defaultBaudRate),
	  port(defaultPort),
	  handle(),
	  buf()
	{

		return;
	}

	Serial::~Serial()
	{

		if(isOpen)
			this->Close();

		return;
	}

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

	short Serial::Read()
	{
		::read(this->handle, &this->buf, 1);

		return short(this->buf);
	}

	// PRIVATE

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
		   std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
		}

		/* Save old tty parameters */
		tty_old = tty;

		/* Set Baud Rate */
		cfsetospeed (&tty, (speed_t)B1000000);
		cfsetispeed (&tty, (speed_t)B1000000);

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
		   std::cout << "Error " << errno << " from tcsetattr" << std::endl;
		}

		return;
	}

}
