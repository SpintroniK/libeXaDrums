#ifndef LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_H
#define LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_H

#include "SpiDev.h"

#include <array>
#include <memory>

namespace IO
{

    static constexpr size_t tenBits{10};
    static constexpr size_t twelveBits{12};
    static constexpr uint8_t eightChannels{8};
    static constexpr uint8_t fourChannels{4};
    
    class MCP3XXX : public SpiDev
    {
        
    public:

        uint32_t ReadChannel(uint8_t channel) const noexcept override
        {		
            const uint32_t data = (uint32_t{0b0001'1000} | channel) << (GetNBits() + 2);
            std::array<uint8_t, 3> spiData {static_cast<uint8_t>((data & 0x00'ff'00'00U) >> 16U), 
                                            static_cast<uint8_t>((data & 0x00'00'ff'00U) >> 8U), 
                                            static_cast<uint8_t>(data  & 0x00'00'00'ffU)}; 

            
            this->DataRW(spiData.data(), spiData.size());
        
            return uint32_t{((spiData[1] << 8U) | spiData[2]) & GetMask()};
        }

    protected:

        MCP3XXX(const std::string& name, size_t dev, size_t cs, size_t bits, uint8_t channels)
        : SpiDev{name, dev, cs, bits, channels}
        {
        }

    private:

    };

    class MCP3008 : public MCP3XXX
    {

    public:
        MCP3008(size_t dev, size_t cs) : MCP3XXX{"MCP3008", dev, cs, tenBits, eightChannels}
        {
        }

    private:
        
    }; 

    class MCP3204 : public MCP3XXX
    {

    public:
        MCP3204(size_t dev, size_t cs) : MCP3XXX{"MCP3204", dev, cs, twelveBits, fourChannels}
        {
        }

    private:
        
    };    

    class MCP3208 : public MCP3XXX
    {

    public:
        MCP3208(size_t dev, size_t cs) : MCP3XXX{"MCP3208", dev, cs, twelveBits, eightChannels}
        {
        }

    private:
        
    };    

} // namespace IO


#endif /* LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_H */
