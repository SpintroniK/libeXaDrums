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

	class SpiDev
	{

	public:

		SpiDev() = delete;
		SpiDev(size_t dev, size_t cs);
		~SpiDev() noexcept { Close(); }

		void Open(size_t speed, int mode) noexcept;
		void Close() noexcept;
		int dataRW(unsigned char* data, size_t len) const noexcept;

	private:

		void operator=(SpiDev const&) = delete;

		static const std::string spiDevPath;
		static const uint8_t bitsPerWord;
		static const uint16_t delay;

		std::string devicePath = "";
		unsigned int clkFreq = 1'000'000;
		int fd = -1;

	};

} /* namespace IO */

#endif /* SOURCE_IO_SPI_H_ */
