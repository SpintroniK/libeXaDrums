/*
 * Spi.h
 *
 *  Created on: 2 May 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H
#define LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H

#include <string>
#include <memory>

#include <unistd.h>

namespace IO
{

	class SpiDev
	{

	public:

		SpiDev(size_t dev, size_t cs, size_t bits, uint8_t channels);
		virtual ~SpiDev() noexcept { Close(); }

		virtual void Open(size_t speed, int mode) noexcept;
		virtual void Close() noexcept;

		virtual uint32_t ReadChannel(uint8_t channel) const noexcept = 0;

		SpiDev(const SpiDev&) = delete;
		SpiDev() = delete;
		void operator=(SpiDev const&) = delete;

	protected:


		int DataRW(uint8_t* data, size_t len) const noexcept;

        const size_t nBits{};
		const uint32_t mask = (1 << nBits) - 1;
        const uint8_t nChannels{};
		
		std::string devicePath;
		unsigned int clkFreq{1'000'000};
		int fd = -1;

		const std::string spiDevPath{"/dev/spidev"};
		const uint8_t bitsPerWord{8};
		const uint16_t delay{0};

	};

	using SpiDevPtr = std::unique_ptr<SpiDev>;

} /* namespace IO */

#endif /* LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H */
