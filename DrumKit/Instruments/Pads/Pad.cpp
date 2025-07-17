/*
 * Pad.cpp
 *
 *  Created on: 11 Jun 2017
 *      Author: jeremy
 */

#include "Pad.h"

#include <algorithm>

using namespace Sound;

namespace DrumKit
{

    Pad::Pad(InstrumentParameters parameters, std::shared_ptr<SoundBank> soundBank)
    : Instrument(parameters, soundBank), soundId(0)
    {
    }

    void Pad::SetTriggers(std::vector<TriggerPtr> const& triggers)
    {

        for (const TriggerPtr& triggerPtr : triggers)
        {

            auto triggerIdAndLocation = std::ranges::find_if(parameters.triggersIdsAndLocations,
                                                             [&triggerPtr](std::pair<int, TriggerLocation> const& idAndLocation)
                                                             { return (idAndLocation.first == triggerPtr->GetId()); });

            if (triggerIdAndLocation != std::end(parameters.triggersIdsAndLocations))
            {

                TriggerLocation triggerLocation = triggerIdAndLocation->second;

                switch (triggerLocation)
                {
                case TriggerLocation::DrumHead: this->trigger = triggerPtr.get(); break;

                default: break;
                }
            }
        }
    }

    std::optional<int> Pad::GetSoundIdFromMidiParams(const IO::MidiMessage& message) const
    {
        if (parameters.soundsInfo.front().midiNote == message.param1)
        {
            return soundId;
        }

        return {};
    }

    void Pad::SetSound(InstrumentSoundInfo const& soundInfo)
    {

        InstrumentSoundType soundType = soundInfo.type;
        std::string soundLocation = soundInfo.soundLocation;

        switch (soundType)
        {
        case InstrumentSoundType::Default: soundId = soundBank->LoadSound(soundLocation, parameters.volume); break;

        default: throw -1; break;
        }
    }

    void Pad::SetVolume(float volume)
    {
        soundBank->SetSoundVolume(soundId, volume);
        parameters.volume = volume;
    }

    void Pad::GetSoundProps(int& id, float& volume) const
    {

        TriggerState triggerState = trigger->GetTriggerState();

        if (triggerState.isTrig)
        {
            id = soundId;
            volume = triggerState.value;
        }
    }

    bool Pad::IsTriggerEvent() const
    {

        TriggerState triggerState = trigger->GetTriggerState();

        return triggerState.isTrig;
    }


    std::vector<TriggerLocation> Pad::GetTriggersLocations() const
    {
        return { TriggerLocation::DrumHead };
    };

    std::vector<int> Pad::GetTriggersIds() const
    {
        return { trigger->GetId() };
    };

    std::vector<InstrumentSoundType> Pad::GetSoundTypes() const
    {
        return { InstrumentSoundType::Default };
    }
} /* namespace DrumKit */
