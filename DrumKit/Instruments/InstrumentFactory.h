/*
 * InstrumentFactory.h
 *
 *  Created on: 15 Jun 2017
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_

#include "../../Util/ErrorHandling.h"
#include "../../Sound/SoundBank/SoundBank.h"
#include "../../Sound/InstrumentSoundType.h"

#include "../Triggers/TriggerType.h"

#include "Cymbals/TestHiHat.h"
#include "Drums/TestDrum.h"
#include "Pads/Pad.h"

#include "Instrument.h"

#include <map>
#include <ranges>
#include <vector>

namespace DrumKit
{

    class InstrumentFactory
    {

    public:

        InstrumentFactory() = default;

        // static InstrumentPtr CreateInstrument(InstrumentType type, InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb)
        // {

        //     switch(type)
        //     {
        //         case InstrumentType::Pad:         return std::make_shared<Pad>(parameters, sb);
        //         case InstrumentType::TestDrum:    return std::make_shared<TestDrum>(parameters, sb);
        //         case InstrumentType::HiHat:       return std::make_shared<TestHiHat>(parameters, sb);
        //     }

        //     throw Util::Exception("Instrument type does not exist.", Util::error_type_error);
        // }

        static std::vector<Sound::InstrumentSoundType>  GetSoundsTypes(const std::string& type)
        {
            return InstrumentFactory{}.Make(type, InstrumentParameters(), nullptr)->GetSoundTypes();
        }

        static std::vector<TriggerLocation>  GetTriggersTypes(const std::string& type)
        {
            return InstrumentFactory{}.Make(type, InstrumentParameters(), nullptr)->GetTriggersLocations();
        }

        InstrumentPtr MakePad(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb) const
        {
            return std::make_shared<Pad>(parameters, sb);
        }
        
        InstrumentPtr MakeTestDrum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb) const
        {
            return std::make_shared<TestDrum>(parameters, sb);
        }

        InstrumentPtr MakeTestHiHat(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb) const
        {
            return std::make_shared<TestHiHat>(parameters, sb);
        }


        InstrumentPtr Make(const std::string& type, InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb) const
        {
            const auto iter = instrumentMap.find(type);

            if(iter == instrumentMap.cend())
            {
                throw Util::Exception("Instrument type doesn't exist.", Util::error_type_error);
            }

            return std::invoke(iter->second, this, parameters, sb); 
        }


        auto GetTypes() &&
        {
            using namespace std::views;
            return std::vector<std::string>{ keys(instrumentMap).begin(), keys(instrumentMap).end() };
        }

    private:
    
        using FactoryPtmf = InstrumentPtr(InstrumentFactory::*)(InstrumentParameters, std::shared_ptr<Sound::SoundBank>) const;
        using InstrumentMap = std::map<std::string, FactoryPtmf>;

        const InstrumentMap instrumentMap
        {
            {"Pad", &InstrumentFactory::MakePad},
            {"DualZonePad", &InstrumentFactory::MakeTestDrum},
            {"TestHiHat", &InstrumentFactory::MakeTestHiHat},
        };

    };


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_ */
