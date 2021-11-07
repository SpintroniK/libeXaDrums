#ifndef LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_H
#define LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_HMCP3008

#include "SpiDev.h"

#include <memory>

namespace IO
{
    
    class MCP3XXX : public SpiDev
    {
        
    public:

        virtual uint32_t ReadChannel(uint8_t channel) const noexcept override
        {		
            const uint32_t data = (0b0001'1000 | channel) << (nBits + 2);
            std::array<uint8_t, 3> spiData {static_cast<uint8_t>((data & 0x00'ff'00'00) >> 16), 
                                            static_cast<uint8_t>((data & 0x00'00'ff'00) >> 8), 
                                            static_cast<uint8_t>(data  & 0x00'00'00'ff)}; 

            
            this->DataRW(spiData.data(), spiData.size());
        
            return static_cast<uint32_t>(((spiData[1] << 8) | spiData[2]) & mask);
        }

    protected:

        MCP3XXX(size_t dev, size_t cs, size_t bits, uint8_t channels)
        : SpiDev{dev, cs, bits, channels}
        {
        }

    private:

    };

    class MCP3008 : public MCP3XXX
    {

    public:
        MCP3008(size_t dev, size_t cs) : MCP3XXX{dev, cs, 10u, 8}
        {
        }

    private:
        
    }; 

    class MCP3204 : public MCP3XXX
    {

    public:
        MCP3204(size_t dev, size_t cs) : MCP3XXX{dev, cs, 12u, 4}
        {
        }

    private:
        
    };    

    class MCP3208 : public MCP3XXX
    {

    public:
        MCP3208(size_t dev, size_t cs) : MCP3XXX{dev, cs, 12u, 8}
        {
        }

    private:
        
    };    

} // namespace IO


#endif /* LIBEXADRUMS_IO_SPIDEVICES_MCP3XXX_H */
