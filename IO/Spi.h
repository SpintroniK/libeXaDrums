/*
 * Spi.h
 *
 *  Created on: 2 May 2017
 *      Author: jeremy
 */

#ifndef SOURCE_IO_SPI_H_
#define SOURCE_IO_SPI_H_

#include <string>

#include <unistd.h>

namespace IO
{

	class Spi
	{

	public:

        static Spi& get()
        {
            static Spi instance;
            return instance;
        }

		void Open(int speed, int mode) noexcept;
		void Close() noexcept;
		int dataRW(unsigned char* data, int len);

	private:

		Spi(Spi const&) = delete;
		void operator=(Spi const&) = delete;

		Spi() : clkFreq(1000000), fd(-1) {}

		static const std::string spiDev0;
		static const uint8_t bitsPerWord;
		static const uint16_t delay;

		unsigned int clkFreq;
		int fd;

	};

} /* namespace IO */

#endif /* SOURCE_IO_SPI_H_ */
