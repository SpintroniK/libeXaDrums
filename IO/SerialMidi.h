#ifndef LIBEXADRUMS_IO_SERIALMIDI_H
#define LIBEXADRUMS_IO_SERIALMIDI_H

#include <array>
#include <optional>
#include <ranges>
#include <string>

#include <cstdio>      // Standard input / output functions
#include <cstdlib>
#include <cstring>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <cerrno>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

namespace IO
{

    static constexpr auto nbBytesPerMessage = 3;
    using MidiBytes_t = std::array<uint8_t, nbBytesPerMessage>;

    struct MidiMessage
    {
        uint8_t command{};
        uint8_t channel{};
        uint8_t param1{};
        uint8_t param2{};

        MidiBytes_t ToBytes() const
        {
            return {static_cast<uint8_t>((command & 0xF0) | (channel & 0x0F)), param1, param2};
        }

        static MidiMessage FromBytes(const MidiBytes_t& bytes)
        {
            MidiMessage message{};   
            message.command = bytes[0] & 0xF0;
            message.channel = bytes[0] & 0x0F;
            message.param1 = bytes[1];
            message.param2 = bytes[2];

            return message;
        }
    };

    class SerialMidi
    {

    public:

        SerialMidi() = default;
        ~SerialMidi() noexcept
        {
            Close();
        }

        void SetPort(const std::string& serialPort) noexcept
        {
            port = serialPort;
        }

        void SetBaudRate(std::size_t br) noexcept
        {
            baudRate = br;
        }

        bool Open()
        {
            handle = ::open(port.data(), O_RDWR);

            termios tty;

            if(tcgetattr(handle, &tty) != 0)
            {
                //error
                return false;
            }

            // Set baud rate
            cfsetospeed(&tty, GetSpeedTFromBaudRate(baudRate));
            cfsetispeed(&tty, GetSpeedTFromBaudRate(baudRate));

            tty.c_cflag &= 	~PARENB;            // Make 8n1
            tty.c_cflag &= 	~CSTOPB;
            tty.c_cflag &= 	~CSIZE;
            tty.c_cflag |= 	CS8;

            tty.c_cflag &= 	~CRTSCTS;           // no flow control
            tty.c_cc[VMIN] = 0;                 // read blocks
            tty.c_cc[VTIME] = 10;               // 1 second read timeout
            tty.c_cflag |=	CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

            // Raw mode
		    cfmakeraw(&tty);

            // Flush Port, then applies attributes
            tcflush(this->handle, TCIFLUSH);
    
            if(tcsetattr (this->handle, TCSANOW, &tty) != 0)
            {
                return false;
            }

            isOpen = true;

            return isOpen;
        }

        void Close()
        {
            if(isOpen)
            {
                ::close(handle);
            }
        }

        uint8_t ReadByte() const
        {
            uint8_t byte{};

            ::read(handle, &byte, sizeof byte);
            
            return byte;        
        }

        std::optional<MidiMessage> GetMessage() const
        {

            MidiBytes_t midiBytes;

            for(auto i : std::views::iota(0, nbBytesPerMessage))
            {
                const auto byte = ReadByte();
                const auto isStatusByte =  byte >> 7 != 0;

                if(!isStatusByte && i == 0)
                {
                    return {};
                }

                midiBytes[i] = byte;
            }

            return MidiMessage::FromBytes(midiBytes);
        }

        auto GetIsOpen() const noexcept { return isOpen; }

    private:

        static speed_t GetSpeedTFromBaudRate(std::size_t baudRate)
        {
            switch(baudRate)
            {
            case 115'200: return static_cast<speed_t>(B115200);
            
            default: return static_cast<speed_t>(B0);
            }
        }

        std::string port{};
        std::size_t baudRate{};
        int handle{};
        bool isOpen{false};

    };
    
} // namespace IO


#endif /* LIBEXADRUMS_IO_SERIALMIDI_H */
