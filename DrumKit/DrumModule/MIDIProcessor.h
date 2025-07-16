#pragma once

#include "../../IO/MIDI.h"
#include <algorithm>
#include <array>

namespace DrumKit
{

    class MIDIProcessor
    {
    public:
        static bool ValidateCommand(std::uint8_t command);

    private:
        static constexpr std::uint8_t max_channel = 0x0F;
        static constexpr std::array<std::uint8_t, 3U> valid_commands{ 0x80, 0x90, 0xA0 };
    };

} // namespace DrumKit