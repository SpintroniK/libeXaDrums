/*
 * TestHiHat.cpp
 *
 *  Created on: 2 Nov 2016
 *      Author: jeremy
 */

#include "TestHiHat.h"

#include "../../../Sound/InstrumentSoundType.h"
#include "../../../Sound/SoundProcessor/SoundProcessor.h"

#include <algorithm>

using namespace Sound;

namespace DrumKit
{

    TestHiHat::TestHiHat(InstrumentParameters parameters, std::shared_ptr<SoundBank> soundBank)
    : Instrument(parameters, soundBank), cymbalSoundId(0)
    {
    }

    void TestHiHat::SetTriggers(const std::vector<TriggerPtr>& triggers)
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
                case TriggerLocation::DrumHead: this->cymbalTrigger = triggerPtr.get(); break;
                case TriggerLocation::Rim: this->pedalTrigger = triggerPtr.get(); break;

                default: break;
                }
            }
        }
    }

    void TestHiHat::SetSound(const InstrumentSoundInfo& soundInfo)
    {

        InstrumentSoundType soundType = soundInfo.type;
        std::string soundLocation = soundInfo.soundLocation;


        switch (soundType)
        {
        case InstrumentSoundType::Default:
        {

            cymbalSoundId = soundBank->LoadSound(soundLocation, parameters.volume);

            for (int i = 0; i < 10; i++)
            {

                const auto& cymbalSound = soundBank->GetSound(cymbalSoundId);
                auto&& newSound = SoundProcessor::Muffle(cymbalSound, 0.25f / float(i + 1));
                int newSoundId = soundBank->AddSound(std::move(newSound), parameters.volume);

                hiHatSoundsIds.push_back(newSoundId);
            }

            break;
        }

        default: throw -1; break;
        }
    }


    std::optional<int> TestHiHat::GetSoundIdFromMidiParams(const IO::MidiMessage& /*message*/) const
    {
        return {};
    }

    void TestHiHat::SetVolume(float volume)
    {

        soundBank->SetSoundVolume(cymbalSoundId, volume);

        std::ranges::for_each(hiHatSoundsIds, [&](const int& id) { soundBank->SetSoundVolume(id, volume); });

        parameters.volume = volume;
    }


    bool TestHiHat::IsTriggerEvent() const
    {

        TriggerState cymbalTriggerState = cymbalTrigger->GetTriggerState();

        return cymbalTriggerState.isTrig;
    }

    void TestHiHat::GetSoundProps(int& id, float& volume) const
    {

        TriggerState cymbalTriggerState = cymbalTrigger->GetTriggerState();
        TriggerState pedalTriggerState = pedalTrigger->GetTriggerState();


        if (cymbalTriggerState.isTrig)
        {

            float pedalPosition = pedalTriggerState.value;
            int hiHatSoundIndex = cymbalSoundId + std::floor(pedalPosition * 10) + 1;


            id = hiHatSoundIndex;
            volume = cymbalTriggerState.value;
        }
    }


    std::vector<InstrumentSoundType> TestHiHat::GetSoundTypes() const
    {
        return { InstrumentSoundType::Default };
    }

    std::vector<TriggerLocation> TestHiHat::GetTriggersLocations() const
    {
        return { TriggerLocation::DrumHead, TriggerLocation::Rim };
    }

    std::vector<int> TestHiHat::GetTriggersIds() const
    {
        return { cymbalTrigger->GetId(), pedalTrigger->GetId() };
    }
} /* namespace DrumKit */
