#ifndef LIBEXADRUMS_IO_SERIALMIDI_H
#define LIBEXADRUMS_IO_SERIALMIDI_H

#include "MIDI.h"

#include <optional>
#include <ranges>
#include <string>

#include <cerrno> // Error number definitions
#include <cstdio> // Standard input / output functions
#include <cstdlib>
#include <cstring>   // String function definitions
#include <fcntl.h>   // File control definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h>  // UNIX standard function definitions

namespace IO
{

    class SerialMidi : public MIDI
    {

    public:
        SerialMidi() = default;
        ~SerialMidi() noexcept
        {
            Close();
        }

        virtual void SetPort(const std::string& serialPort) noexcept override
        {
            port = serialPort;
        }

        void SetBaudRate(std::size_t br) noexcept
        {
            baudRate = br;
        }

        virtual bool Open() override
        {
            handle = ::open(port.data(), O_RDWR);

            termios tty;

            if (tcgetattr(handle, &tty) != 0)
            {
                // error
                return false;
            }

            // Set baud rate
            cfsetospeed(&tty, GetSpeedTFromBaudRate(baudRate));
            cfsetispeed(&tty, GetSpeedTFromBaudRate(baudRate));

            tty.c_cflag &= ~PARENB; // Make 8n1
            tty.c_cflag &= ~CSTOPB;
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS8;

            tty.c_cflag &= ~CRTSCTS;       // no flow control
            tty.c_cc[VMIN] = 0;            // read blocks
            tty.c_cc[VTIME] = 10;          // 1 second read timeout
            tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines

            // Raw mode
            cfmakeraw(&tty);

            // Flush Port, then applies attributes
            tcflush(this->handle, TCIFLUSH);

            if (tcsetattr(this->handle, TCSANOW, &tty) != 0)
            {
                return false;
            }

            isOpen = true;

            return isOpen;
        }

        virtual void Close() override
        {
            if (isOpen)
            {
                ::close(handle);
            }
        }

        [[nodiscard]] uint8_t ReadByte() const
        {
            uint8_t byte{};

            [[maybe_unused]] const auto result = ::read(handle, &byte, sizeof byte);

            return byte;
        }

        virtual std::optional<MidiMessage> GetMessage() const override
        {

            MidiBytes_t midiBytes;

            for (auto i : std::views::iota(0, nbBytesPerMessage))
            {
                const auto byte = ReadByte();
                const auto isStatusByte = byte >> 7 != 0;

                if (!isStatusByte && i == 0)
                {
                    return {};
                }

                midiBytes[i] = byte;
            }

            return MidiMessage::FromBytes(midiBytes);
        }

        virtual bool GetIsOpen() const noexcept override
        {
            return isOpen;
        }

    private:
        static speed_t GetSpeedTFromBaudRate(std::size_t baudRate)
        {
            switch (baudRate)
            {
            case 115'200: return static_cast<speed_t>(B115200);

            default: return static_cast<speed_t>(B0);
            }
        }

        std::string port{};
        std::size_t baudRate{};
        int handle{};
        bool isOpen{ false };
    };

} // namespace IO


#endif /* LIBEXADRUMS_IO_SERIALMIDI_H */
