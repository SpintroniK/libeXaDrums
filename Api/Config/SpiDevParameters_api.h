#ifndef LIBEXADRUMS_API_CONFIG_SPIDEVPARAMETERS_API_H
#define LIBEXADRUMS_API_CONFIG_SPIDEVPARAMETERS_API_H

#include "../../IO/SpiDevices/SpiDevParameters.h"

#include <cstring>

namespace eXaDrumsApi
{

    struct SpiDevParameters
    {

        SpiDevParameters(const char* names, unsigned int bus, unsigned int cs)
        {
            *this = IO::SpiDevParameters{names, bus, cs};
        }

        explicit SpiDevParameters(const IO::SpiDevParameters& params) noexcept
        {
            *this = params;
        }

        explicit operator IO::SpiDevParameters() const noexcept
        {
            IO::SpiDevParameters params{this->name, this->bus, this->cs};
            return params;
        }

        SpiDevParameters& operator=(const IO::SpiDevParameters& params) noexcept
        {
            this->bus = params.bus;
            this->cs = params.cs;

            std::snprintf(this->name, sizeof this->name, "%s", params.name.data());

            return *this;
        }
        

        unsigned int bus;
        unsigned int cs;      
        char name[64];  

    };
    
} // namespace eXaDrumsApi


#endif /* LIBEXADRUMS_API_CONFIG_SPIDEVPARAMETERS_API_H */
