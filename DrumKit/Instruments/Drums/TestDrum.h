/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_

#include "../../../IO/MIDI.h"
#include "../../../Sound/InstrumentSoundType.h"
#include "../../../Sound/SoundBank/SoundBank.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <memory>
#include <vector>


namespace DrumKit
{

    class TestDrum : public Instrument
    {

    public:
        TestDrum(const TestDrum&) = default;
        TestDrum(TestDrum&&) = delete;
        TestDrum& operator=(const TestDrum&) = default;
        TestDrum& operator=(TestDrum&&) = delete;
        TestDrum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
        virtual ~TestDrum() = default;

        void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
        void SetSound(InstrumentSoundInfo const& soundInfo) final;
        void SetVolume(float volume) final;

        [[nodiscard]] bool IsTriggerEvent() const final;
        void GetSoundProps(int& id, float& volume) const final;

        [[nodiscard]] std::optional<int> GetSoundIdFromMidiParams(const IO::MidiMessage& message) const final;

        [[nodiscard]] std::vector<Sound::InstrumentSoundType> GetSoundTypes() const final
        {
            return { Sound::InstrumentSoundType::Default, Sound::InstrumentSoundType::RimShot };
        }
        [[nodiscard]] std::vector<TriggerLocation> GetTriggersLocations() const final
        {
            return { TriggerLocation::DrumHead, TriggerLocation::Rim };
        };
        [[nodiscard]] std::vector<int> GetTriggersIds() const final
        {
            return { drumHeadTrigger->GetId(), drumRimTrigger->GetId() };
        };

    private:
        Trigger* drumHeadTrigger;
        Trigger* drumRimTrigger;

        int drumHeadSoundId;
        int drumRimSoundId;
    };

} // namespace DrumKit


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
