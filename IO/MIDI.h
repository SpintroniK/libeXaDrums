#ifndef LIBEXADRUMS_IO_MIDI_H
#define LIBEXADRUMS_IO_MIDI_H

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace IO
{
    struct MidiMessage;

    class MIDI
    {
    public:
        MIDI() = default;
        MIDI(const MIDI&) = default;
        MIDI(MIDI&&) = delete;
        MIDI& operator=(const MIDI&) = default;
        MIDI& operator=(MIDI&&) = delete;
        virtual ~MIDI() = default;

        virtual void SetPort(const std::string&) noexcept = 0;
        virtual bool Open() = 0;
        virtual void Close() = 0;
        virtual void SetBaudRate(std::size_t baud_rate) noexcept = 0;
        [[nodiscard]] virtual std::optional<MidiMessage> GetMessage() const = 0;

        [[nodiscard]] virtual bool GetIsOpen() const noexcept = 0;

    protected:
    private:
    };

    using MIDIPtr = std::unique_ptr<MIDI>;

    static constexpr auto nbBytesPerMessage = 3;
    using MidiBytes_t = std::array<uint8_t, nbBytesPerMessage>;

    struct MidiMessage
    {
        uint8_t command{};
        uint8_t channel{};
        uint8_t param1{};
        uint8_t param2{};

        [[nodiscard]] MidiBytes_t ToBytes() const
        {
            return { static_cast<uint8_t>((command & 0xF0) | (channel & 0x0F)), param1, param2 };
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

} // namespace IO


#endif /* LIBEXADRUMS_IO_MIDI_H */