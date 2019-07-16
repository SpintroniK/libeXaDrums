/*
 * Spi.cpp
 *
 *  Created on: 2 May 2017
 *      Author: jeremy
 */

#include "Spi.h"


#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


namespace IO
{

	const std::string Spi::spiDev0 = "/dev/spidev0.0";
	const uint8_t Spi::bitsPerWord = 8;
	const uint16_t Spi::delay = 0;


	void Spi::Open(int freq, int mode) noexcept
	{

		this->clkFreq = freq;

		this->fd = open(Spi::spiDev0.c_str(), O_RDWR);


	  	mode &= 3;


		ioctl(this->fd, SPI_IOC_WR_MODE, &mode);
		ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &Spi::bitsPerWord);
		ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &this->clkFreq);


		return;
	}

	void Spi::Close() noexcept
	{

		if(fd != -1)
		{
			close(this->fd);
			fd = -1;
		}

		return;
	}

	int Spi::dataRW(unsigned char* data, int len)
	{

		struct spi_ioc_transfer spiData{};

		spiData.tx_buf = (unsigned long)data;
		spiData.rx_buf = (unsigned long)data;

		spiData.len = len ;
		spiData.speed_hz = this->clkFreq;

		spiData.delay_usecs = 0;
		spiData.bits_per_word = Spi::bitsPerWord;
		spiData.cs_change = 0;
		spiData.pad = 0;

		return ioctl(this->fd, SPI_IOC_MESSAGE(1), &spiData);
	}



} /* namespace IO */
