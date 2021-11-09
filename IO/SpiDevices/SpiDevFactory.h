#ifndef LIBEXADRUMS_IO_SPIDEVICES_SPIDEVFACTORY_H
#define LIBEXADRUMS_IO_SPIDEVICES_SPIDEVFACTORY_H

#include "../../Util/ErrorHandling.h"

#include "MCP3XXX.h"
#include "SpiDev.h"

#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

namespace IO
{
    
    class SpiDevFactory
    {
     
    public:
        SpiDevFactory() = default;

        SpiDevPtr MakeMCP3008(size_t dev, size_t cs) const
        {
            return std::make_unique<MCP3008>(dev, cs);
        }

        SpiDevPtr MakeMCP3204(size_t dev, size_t cs) const
        {
            return std::make_unique<MCP3204>(dev, cs);
        }

        SpiDevPtr MakeMCP3208(size_t dev, size_t cs) const
        {
            return std::make_unique<MCP3208>(dev, cs);
        }

        SpiDevPtr Make(const std::string& type, size_t dev, size_t cs) &&
        {
            auto iter = spiDevMap.find(type);

            if(iter == spiDevMap.end())
            {
                throw Util::Exception("Spi device type doesn't exist.", Util::error_type_error);
            }

            return (this->*iter->second)(dev, cs); 
        }

        auto GetTypes() &&
        {
            using namespace std::views;
            return std::vector<std::string>{ keys(spiDevMap).begin(), keys(spiDevMap).end() };
        }

    private:

        using FactoryPtmf = SpiDevPtr(SpiDevFactory::*)(size_t, size_t) const;
        using SpiDevMap = std::map<std::string, FactoryPtmf>;

        const SpiDevMap spiDevMap
        {
            {"MCP3008", &SpiDevFactory::MakeMCP3008},
            {"MCP3204", &SpiDevFactory::MakeMCP3204},
            {"MCP3208", &SpiDevFactory::MakeMCP3208},
        };

    };

} // namespace IO


#endif /* LIBEXADRUMS_IO_SPIDEVICES_SPIDEVFACTORY_H */
