/*
 * Pad.h
 *
 *  Created on: 11 Jun 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H
#define LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H

#include "../../../IO/MIDI.h"
#include "../../../Sound/InstrumentSoundType.h"
#include "../../../Sound/SoundBank/SoundBank.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <memory>
#include <vector>

namespace DrumKit
{

    class Pad : public Instrument
    {

    public:
        Pad(const Pad&) = default;
        Pad(Pad&&) = delete;
        Pad& operator=(const Pad&) = default;
        Pad& operator=(Pad&&) = delete;
        Pad(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
        ~Pad() = default;

        void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
        void SetSound(InstrumentSoundInfo const& soundInfo) final;
        void SetVolume(float volume) final;

        void GetSoundProps(int& id, float& volume) const final;
        bool IsTriggerEvent() const final;

        [[nodiscard]] std::optional<int> GetSoundIdFromMidiParams(const IO::MidiMessage& message) const final;

        [[nodiscard]] std::vector<Sound::InstrumentSoundType> GetSoundTypes() const final;

        [[nodiscard]] std::vector<TriggerLocation> GetTriggersLocations() const final;

        [[nodiscard]] std::vector<int> GetTriggersIds() const final;

    private:
        Trigger* trigger;
        int soundId;
    };

} /* namespace DrumKit */

#endif /* LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H */
