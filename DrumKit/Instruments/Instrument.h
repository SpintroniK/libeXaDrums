/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_INSTRUMENTS_INSTRUMENT_H
#define LIBEXADRUMS_DRUMKIT_INSTRUMENTS_INSTRUMENT_H


#include "../../IO/MIDI.h"
#include "../../Sound/SoundBank/SoundBank.h"

#include "../Triggers/Triggers/Trigger.h"

#include "InstrumentParameters.h"

#include <memory>
#include <optional>
#include <vector>

namespace DrumKit
{

    class Instrument
    {

    public:
        Instrument(const Instrument&) = default;
        Instrument(Instrument&&) = delete;
        Instrument& operator=(const Instrument&) = default;
        Instrument& operator=(Instrument&&) = delete;
        Instrument(const InstrumentParameters& parameters, std::shared_ptr<Sound::SoundBank> sb);

        virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) = 0;
        virtual void SetSound(InstrumentSoundInfo const& soundInfo) = 0;
        virtual void SetVolume(float volume) = 0;

        virtual void GetSoundProps(int& id, float& volume) const = 0;
        [[nodiscard]] virtual bool IsTriggerEvent() const = 0;

        [[nodiscard]] virtual std::optional<int> GetSoundIdFromMidiParams(const IO::MidiMessage& message) const = 0;

        [[nodiscard]] virtual int GetId() const
        {
            return this->parameters.id;
        }

        [[nodiscard]] virtual float GetVolume() const
        {
            return this->parameters.volume;
        }

        [[nodiscard]] virtual std::string GetName() const
        {
            return this->parameters.instrumentName;
        }

        [[nodiscard]] virtual std::vector<Sound::InstrumentSoundType> GetSoundTypes() const = 0;
        [[nodiscard]] virtual std::vector<TriggerLocation> GetTriggersLocations() const = 0;
        [[nodiscard]] virtual std::vector<int> GetTriggersIds() const = 0;

    protected:
        ~Instrument() = default;

        InstrumentParameters parameters;
        std::shared_ptr<Sound::SoundBank> soundBank;
        // std::map<int, int> soundIds;


    private:
    };

    typedef std::shared_ptr<Instrument> InstrumentPtr;

} // namespace DrumKit

#endif /* LIBEXADRUMS_DRUMKIT_INSTRUMENTS_INSTRUMENT_H */
