#ifndef LIBEXADRUMS_IO_SPIDEVICES_SPIDEVPARAMETERS_H
#define LIBEXADRUMS_IO_SPIDEVICES_SPIDEVPARAMETERS_H

#include <string>

namespace IO
{
    /**
     * @brief Defines SPI device external parameters.
     * 
     * These parameters are the bus id, chip select (cs), the device name.
     */
    struct SpiDevParameters
    {
        /**
         * @brief Construct a new External Parameters object
         * 
         * @param name Name of the SPI device
         * @param bus Bus id of the device
         * @param cs Chip select for tat device
         */
        SpiDevParameters(const std::string& name, size_t bus, size_t cs)
        : name{name}, bus{bus}, cs{cs}
        {

        }
        
        const std::string name;
        const size_t bus;
        const size_t cs;
    };
} // namespace IO


#endif /* LIBEXADRUMS_IO_SPIDEVICES_SPIDEVPARAMETERS_H */
