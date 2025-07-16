#include "MIDIProcessor.h"

bool DrumKit::MIDIProcessor::ValidateCommand(std::uint8_t command)
{
    const auto type = command & static_cast<std::uint8_t>(0xF0);
    const auto channel = command & static_cast<std::uint8_t>(0x0F);

    if (channel > max_channel)
    {
        return false;
    }

    return std::ranges::count(valid_commands, type) > 0;
}
