#ifndef LIBEXADRUMS_SOURCE_IO_SENSOR_FACTORY_H_
#define LIBEXADRUMS_SOURCE_IO_SENSOR_FACTORY_H_

#include "../Util/ErrorHandling.h"

#include "ISensor.h"
#include "SpiSensor.h"
#include "HddSensor.h"
#include "VirtualSensor.h"

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <tuple>
#include <array>

namespace IO
{

    class SensorFactory
    {
    public:


        SensorFactory() = default;

        SensorFactory(const std::string& dataFolder)
        : dataFolder{dataFolder}
        {

        }

        ~SensorFactory() = default;

        ISensorPtr MakeVirtual(size_t channel) const
        {
            return std::move(std::make_unique<VirtualSensor>(channel));
        }

        ISensorPtr MakeSpi(const std::vector<SpiDev>* spidev, size_t channel) const
        {
            // TODO: Make this work with more than one spi device.
            return std::move(std::make_unique<SpiSensor>(&spidev->front(), channel));
        }

        ISensorPtr MakeHdd(const std::string& dataFolder, size_t channel) const
        {
            return std::move(std::make_unique<HddSensor>(dataFolder, channel));
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

        void SetSpiDev(const std::vector<SpiDev>& spidev_)
        {
            this->spidev = &spidev_;
        }

        void SetDataFolder(const std::string& hddDataFolder)
        {
            this->dataFolder = hddDataFolder;
        }

        static constexpr const auto Types = std::array{"Virtual", "Spi", "Hdd"};

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

        const std::vector<SpiDev>* spidev{nullptr};
        std::string dataFolder{};

        const SensorMap sensorMap
        {
            {Types[0], &SensorFactory::MakeVirtual},
            {Types[1], &SensorFactory::MakeSpi},
            {Types[2], &SensorFactory::MakeHdd},
        };

    };

}

#endif