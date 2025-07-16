#ifndef LIBEXADRUMS_IO_USBMIDI_H
#define LIBEXADRUMS_IO_USBMIDI_H

#include "MIDI.h"

#include <alsa/asoundlib.h>

#include <array>
#include <optional>
#include <string>

namespace IO
{

    class USBMIDI : public MIDI
    {
    public:
        USBMIDI() = default;
        ~USBMIDI()
        {
            Close();
        }

        virtual void SetPort(const std::string& midiPort) noexcept override
        {
            portName = midiPort;
        }

        virtual void SetBaudRate(std::size_t br) noexcept override
        {
            baudRate = br;
        }

        virtual bool Open() override
        {
            const auto status = snd_rawmidi_open(&midiIn, nullptr, "hw:1,0,0", SND_RAWMIDI_SYNC);
            return status >= 0;
        }

        virtual void Close() override
        {
            if (midiIn != nullptr)
            {
                snd_rawmidi_close(midiIn);
                midiIn = nullptr;
            }
        }

        virtual std::optional<MidiMessage> GetMessage() const override
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

        virtual bool GetIsOpen() const noexcept override
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