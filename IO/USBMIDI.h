#ifndef LIBEXADRUMS_IO_USBMIDI_H
#define LIBEXADRUMS_IO_USBMIDI_H

#include "MIDI.h"

#include <alsa/asoundlib.h>

#include <optional>
#include <string>

namespace IO
{

    class USBMIDI : public MIDI
    {
    public:
        USBMIDI() = default;
        USBMIDI(const USBMIDI&) = default;
        USBMIDI(USBMIDI&&) = delete;
        USBMIDI& operator=(const USBMIDI&) = default;
        USBMIDI& operator=(USBMIDI&&) = delete;

        ~USBMIDI() override
        {
            Close();
        }

        void SetPort(const std::string& midiPort) noexcept override
        {
            portName = midiPort;
        }

        void SetBaudRate(std::size_t baud_rate) noexcept override
        {
            baudRate = baud_rate;
        }

        bool Open() override
        {
            const auto status = snd_rawmidi_open(&midiIn, nullptr, "hw:1,0,0", SND_RAWMIDI_SYNC);
            return status >= 0;
        }

        void Close() override
        {
            if (midiIn != nullptr)
            {
                snd_rawmidi_close(midiIn);
                midiIn = nullptr;
            }
        }

        [[nodiscard]] std::optional<MidiMessage> GetMessage() const override
        {
            MidiBytes_t midiBytes;

            if (midiIn == nullptr)
            {
                return {};
            }

            const auto status = snd_rawmidi_read(midiIn, midiBytes.data(), midiBytes.size());

            if (static_cast<size_t>(status) != midiBytes.size())
            {
                return {};
            }

            return MidiMessage::FromBytes(midiBytes);
        }

        [[nodiscard]] bool GetIsOpen() const noexcept override
        {
            return midiIn != nullptr;
        }

    private:
        snd_rawmidi_t* midiIn = nullptr;
        std::string portName;
        std::size_t baudRate{};
    };


} // namespace IO


#endif /* LIBEXADRUMS_IO_USBMIDI_H */