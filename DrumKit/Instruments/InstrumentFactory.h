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

#include "InstrumentType.h"
#include "Instrument.h"

#include <vector>

namespace DrumKit
{

	class InstrumentFactory
	{

	public:

		static InstrumentPtr CreateInstrument(InstrumentType type, InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb)
		{

			switch(type)
			{
				case InstrumentType::Pad: 		return std::make_shared<Pad>(parameters, sb);
				case InstrumentType::TestDrum: 	return std::make_shared<TestDrum>(parameters, sb);
				case InstrumentType::HiHat: 	return std::make_shared<TestHiHat>(parameters, sb);
			}

			throw Util::Exception("Instrument type does not exist.", Util::error_type_error);
		}

		static std::vector<Sound::InstrumentSoundType>  GetSoundsTypes(InstrumentType type)
		{
			return CreateInstrument(type, InstrumentParameters(), nullptr)->GetSoundTypes();
		}

		static std::vector<TriggerLocation>  GetTriggersTypes(InstrumentType type)
		{
			return CreateInstrument(type, InstrumentParameters(), nullptr)->GetTriggersLocations();
		}


	private:

		InstrumentFactory() = delete;
		~InstrumentFactory() = delete;


	};


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_ */
