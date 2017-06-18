/*
 * InstrumentFactory.h
 *
 *  Created on: 15 Jun 2017
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_

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
				case InstrumentType::Pad: 		return InstrumentPtr(new Pad(parameters, sb));
				case InstrumentType::TestDrum: 	return InstrumentPtr(new TestDrum(parameters, sb));
				case InstrumentType::HiHat: 	return InstrumentPtr(new TestHiHat(parameters, sb));
			}

			throw -1;
		}

		static std::vector<Sound::InstrumentSoundType>  GetSoundsTypes(InstrumentType type)
		{

			switch(type)
			{
				case InstrumentType::TestDrum: 	return TestDrum::soundsTypes;
				case InstrumentType::Pad: 		return Pad::soundsTypes;
				case InstrumentType::HiHat: 	return TestHiHat::soundsTypes;
			}


			throw -1;
		}

		static std::vector<TriggerLocation>  GetTriggersTypes(InstrumentType type)
		{

			switch(type)
			{
				case InstrumentType::TestDrum: 	return TestDrum::triggersLocations;
				case InstrumentType::Pad: 		return Pad::triggersLocations;
				case InstrumentType::HiHat: 	return TestHiHat::triggersLocations;
			}

			throw -1;
		}


	private:

		InstrumentFactory() = delete;
		~InstrumentFactory() = delete;


	};


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTFACTORY_H_ */
