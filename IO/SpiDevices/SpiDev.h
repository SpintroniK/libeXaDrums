/*
 * Spi.h
 *
 *  Created on: 2 May 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H
#define LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H

#include <memory>
#include <string>

#include <unistd.h>

namespace IO
{

	class SpiDev
	{

	public:

		/**
		 * @brief Construct a new SpiDev object
		 * 
		 * Only ADC devices are supported, so the number of bits and channels are required.
		 * This represents a spidev resource, so it can be opened, closed, and transfer data.
		 * 
		 * @param dev Device number
		 * @param cs Chip select
		 * @param bits Number of bits (ADC device)
		 * @param channels Number of channels
		 */
		SpiDev(size_t dev, size_t cs, size_t bits, uint8_t channels);
		~SpiDev() noexcept { Close(); }

		/**
		 * @brief Open SPI device
		 * 
		 * @param speed Clock frequency, in Hz
		 * @param mode SPI mode
		 */
		void Open(size_t speed, int mode) noexcept;

		/**
		 * @brief Close SPI device
		 * 
		 */
		void Close() noexcept;

		/**
		 * @brief Read SPI ADC channel
		 * 
		 * @param channel Channel number
		 * @return uint32_t Value that's been returned by the ADC
		 */
		virtual uint32_t ReadChannel(uint8_t channel) const noexcept = 0;

		/**
		 * @brief Get the Nb Channels of the ADC
		 * 
		 * @return uint8_t Number of channels
		 */
		virtual uint8_t GetNbChannels() const noexcept { return nChannels; }

		SpiDev(const SpiDev&) = delete;
		SpiDev(SpiDev&&) = delete;
		SpiDev() = delete;
		void operator=(SpiDev const&) = delete;
		void operator=(SpiDev&&) = delete;

	protected:


		int DataRW(uint8_t* data, size_t len) const noexcept;
		auto GetNBits() const { return nBits; }
		auto GetMask() const { return mask; }
	
	private:

        const size_t nBits{};
		const uint32_t mask = (1U << nBits) - 1U;
        const uint8_t nChannels{};
		
		std::string devicePath;
		unsigned int clkFreq{};
		int fd = -1;

		const std::string spiDevPath{"/dev/spidev"};
		const uint8_t bitsPerWord{8};
		const uint16_t delay{0};

	};

	using SpiDevPtr = std::unique_ptr<SpiDev>;

} /* namespace IO */

#endif /* LIBEXADRUMS_IO_SPIDEVICES_SPIDEV_H */
