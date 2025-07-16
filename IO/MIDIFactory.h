#ifndef LIBEXADRUMS_IO_MIDIFACTORY_H
#define LIBEXADRUMS_IO_MIDIFACTORY_H

#include "../Util/ErrorHandling.h"
#include "MIDI.h"
#include "SerialMidi.h"
#include "USBMIDI.h"

#include <concepts>
#include <functional>
#include <string>
#include <unordered_map>

namespace IO
{
    class MIDIFactory
    {
    public:
        MIDIFactory() = delete;
        MIDIFactory(const MIDIFactory&) = default;
        MIDIFactory(MIDIFactory&&) = delete;
        MIDIFactory& operator=(const MIDIFactory&) = default;
        MIDIFactory& operator=(MIDIFactory&&) = delete;
        ~MIDIFactory() = delete;

        template <typename Midi_t>
            requires std::derived_from<Midi_t, MIDI>
        static MIDIPtr MakeMidi()
        {
            return std::make_unique<Midi_t>();
        }

        static MIDIPtr Make(const std::string& type)
        {
            if (!midiMap.contains(type))
            {
                throw Util::Exception("MIDI interface not supported.", Util::error_type_error);
            }

            return std::invoke(midiMap.at(type));
        }

    private:
        static inline const std::unordered_map<std::string, MIDIPtr (*)()> midiMap{
            { "USBMidi", &MIDIFactory::MakeMidi<USBMIDI> },
            { "SerialMidi", &MIDIFactory::MakeMidi<SerialMidi> },
        };
    };

} // namespace IO


#endif /* LIBEXADRUMS_IO_MIDIFACTORY_H */