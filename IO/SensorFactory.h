#ifndef LIBEXADRUMS_IO_SENSORFACTORY_H
#define LIBEXADRUMS_IO_SENSORFACTORY_H

#include "../Util/ErrorHandling.h"

#include "ISensor.h"
#include "SpiSensor.h"
#include "HddSensor.h"
#include "VirtualSensor.h"

#include <array>
#include <map>
#include <ranges>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace IO
{

    class SensorFactory
    {
    public:


        SensorFactory() = default;

        SensorFactory(std::string dataFolder)
        : dataFolder{std::move(dataFolder)}
        {

        }


        ISensorPtr MakeVirtual(size_t channel) const
        {
            return std::make_unique<VirtualSensor>(channel);
        }

        ISensorPtr MakeSpi(const std::vector<SpiDevPtr>* spidev, size_t channel) const
        {
            // TODO: Make this work with more than one spi device.
            return std::make_unique<SpiSensor>(spidev->front().get(), channel);
        }

        ISensorPtr MakeHdd(const std::string& dataFolder, size_t channel) const
        {
            return std::make_unique<HddSensor>(dataFolder, channel);
        }

        ISensorPtr Make(const std::string& type, size_t channel) const
        {
            auto iter = sensorMap.find(type);

            if(iter == sensorMap.end())
            {
                throw Util::Exception("Sensor type doesn't exist.", Util::error_type_error);
            }

            return (this->*iter->second)(channel); 
        }

        void SetSpiDev(const std::vector<SpiDevPtr>& spidev_)
        {
            this->spidev = &spidev_;
        }

        void SetDataFolder(const std::string& hddDataFolder)
        {
            this->dataFolder = hddDataFolder;
        }

        auto GetTypes() &&
        {
            using namespace std::views;
            return std::vector<std::string>{ keys(sensorMap).begin(), keys(sensorMap).end() };
        }


    private:

        ISensorPtr MakeSpi(size_t channel) const
        {
            return MakeSpi(this->spidev, channel);
        }

        ISensorPtr MakeHdd(size_t channel) const
        {
            return MakeHdd(this->dataFolder, channel);
        }

        using FactoryPtmf = ISensorPtr(SensorFactory::*)(size_t) const;
        using SensorMap = std::map<std::string, FactoryPtmf>;

        const std::vector<SpiDevPtr>* spidev{nullptr};
        std::string dataFolder{};

        const SensorMap sensorMap
        {
            {"Virtual", &SensorFactory::MakeVirtual},
            {"Spi", &SensorFactory::MakeSpi},
            {"Hdd", &SensorFactory::MakeHdd},
        };

    };

}

#endif /* LIBEXADRUMS_IO_SENSORFACTORY_H */
