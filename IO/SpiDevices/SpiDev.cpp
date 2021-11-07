/*
 * Spi.cpp
 *
 *  Created on: 2 May 2017
 *      Author: jeremy
 */

#include "SpiDev.h"


#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

namespace IO
{


	SpiDev::SpiDev(size_t dev, size_t cs, size_t bits, uint8_t channels)
	: nBits{bits}, nChannels{channels}
	{
		this->devicePath = spiDevPath + std::to_string(dev) + "." + std::to_string(cs);
	}

	void SpiDev::Open(size_t freq, int mode) noexcept
	{

		this->clkFreq = freq;

		this->fd = open(devicePath.c_str(), O_RDWR);

	  	mode &= 3;


		ioctl(this->fd, SPI_IOC_WR_MODE, &mode);
		ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
		ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &this->clkFreq);
		
	}

	void SpiDev::Close() noexcept
	{

		if(fd != -1)
		{
			close(this->fd);
			fd = -1;
		}

		return;
	}

	

	int SpiDev::DataRW(uint8_t* data, size_t len) const noexcept
	{

		spi_ioc_transfer spiData{};

		spiData.tx_buf = reinterpret_cast<decltype(spiData.tx_buf)>(data);
		spiData.rx_buf = reinterpret_cast<decltype(spiData.rx_buf)>(data);

		spiData.len = len ;
		spiData.speed_hz = this->clkFreq;

		spiData.delay_usecs = 0;
		spiData.bits_per_word = SpiDev::bitsPerWord;
		spiData.cs_change = 0;
		spiData.pad = 0;

		return ioctl(this->fd, SPI_IOC_MESSAGE(1), &spiData);
	}



} /* namespace IO */
