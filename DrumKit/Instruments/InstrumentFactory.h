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

#include <concepts>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace DrumKit
{

    class InstrumentFactory
    {

    public:

        InstrumentFactory() = delete;
        ~InstrumentFactory() = delete;

        static inline std::vector<Sound::InstrumentSoundType>  GetSoundsTypes(const std::string& type)
        {
            return InstrumentFactory::Make(type, InstrumentParameters{}, nullptr)->GetSoundTypes();
        }

        static inline std::vector<TriggerLocation>  GetTriggersTypes(const std::string& type)
        {
            return InstrumentFactory::Make(type, InstrumentParameters{}, nullptr)->GetTriggersLocations();
        }

        template <typename Instrument_t>
        static inline InstrumentPtr MakeInstrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb)
        {
            return std::make_shared<Instrument_t>(parameters, sb);
        }
        

        static inline InstrumentPtr Make(const std::string& type, InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb)
        {

            if(!instrumentMap.contains(type))
            {
                throw Util::Exception("Instrument type doesn't exist.", Util::error_type_error);
            }

            return std::invoke(instrumentMap.at(type), parameters, sb); 
        }


        static inline auto GetTypes()
        {
            using namespace std::views;
            return std::vector<std::string>{ keys(instrumentMap).begin(), keys(instrumentMap).end() };
        }

    private:
    
        using FactoryPtmf = InstrumentPtr(*)(InstrumentParameters, std::shared_ptr<Sound::SoundBank>);
        using InstrumentMap = std::unordered_map<std::string, FactoryPtmf>;

        static inline const InstrumentMap instrumentMap
        {
            {"Pad", &InstrumentFactory::MakeInstrument<Pad>},
            {"DualZonePad", &InstrumentFactory::MakeInstrument<TestDrum>},
            {"TestHiHat", &InstrumentFactory::MakeInstrument<TestHiHat>},
        };

    };


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_ */
