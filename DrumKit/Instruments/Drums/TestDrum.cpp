/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "TestDrum.h"


#include <algorithm>

using namespace Sound;

namespace DrumKit
{

    TestDrum::TestDrum(InstrumentParameters parameters, std::shared_ptr<SoundBank> soundBank)
    : Instrument(parameters, soundBank), drumHeadSoundId(0), drumRimSoundId(0)
    {
    }


    void TestDrum::SetTriggers(std::vector<TriggerPtr> const& triggers)
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
                case TriggerLocation::DrumHead: this->drumHeadTrigger = triggerPtr.get(); break;
                case TriggerLocation::Rim: this->drumRimTrigger = triggerPtr.get(); break;

                default: break;
                }
            }
        }
    }

    void TestDrum::SetSound(InstrumentSoundInfo const& soundInfo)
    {

        InstrumentSoundType soundType = soundInfo.type;
        std::string soundLocation = soundInfo.soundLocation;

        switch (soundType)
        {
        case InstrumentSoundType::RimShot:
            drumRimSoundId = soundBank->LoadSound(soundLocation, parameters.volume);
            break;
        case InstrumentSoundType::Default:
            drumHeadSoundId = soundBank->LoadSound(soundLocation, parameters.volume);
            break;

        default: throw -1; break;
        }
    }


    std::optional<int> TestDrum::GetSoundIdFromMidiParams(const IO::MidiMessage& /* message */) const
    {
        return {};
    }

    void TestDrum::SetVolume(float volume)
    {

        soundBank->SetSoundVolume(drumRimSoundId, volume);
        soundBank->SetSoundVolume(drumHeadSoundId, volume);

        parameters.volume = volume;
    }

    bool TestDrum::IsTriggerEvent() const
    {

        TriggerState headTriggerState = drumHeadTrigger->GetTriggerState();
        TriggerState rimTriggerState = drumRimTrigger->GetTriggerState();

        return headTriggerState.isTrig || rimTriggerState.isTrig;
    }

    void TestDrum::GetSoundProps(int& id, float& volume) const
    {

        TriggerState headTriggerState = drumHeadTrigger->GetTriggerState();
        TriggerState rimTriggerState = drumRimTrigger->GetTriggerState();


        if (headTriggerState.isTrig)
        {
            id = drumHeadSoundId;
            volume = headTriggerState.value;
        }
        else if (rimTriggerState.isTrig)
        {
            id = drumRimSoundId;
            volume = rimTriggerState.value;
        }
    }
    // PRIVATE

    /*void Drum::GenerateSounds()
    {

        std::function<void(InstrumentSoundInfo)> genSounds = [this](InstrumentSoundInfo soundInfo)
        {

            std::vector<short> soundData;
            unsigned int soundDuration;

            // Load sound
            //Sound::SoundBank::LoadSound(soundInfo.soundLocation, soundData, soundDuration);

            switch (soundInfo.type)
            {
                case Sound::InstrumentSoundType::Default:

                        int id;
                        //soundProcessor->AddSound(id, soundData);

                        // Internal Id = 0 for default sound
                        soundIds.insert(std::pair<int, int>(0, id));

                    break;
                default:
                    break;
            }




        };


        std::for_each(parameters.soundsInfo.cbegin(), parameters.soundsInfo.cend(), genSounds);

        return;
    }
    */
} // namespace DrumKit
