/*
 * Instrument.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */


#include "Instrument.h"

namespace DrumKit
{

	Instrument::Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor, std::map<int, std::shared_ptr<Trigger>> const& trigs)
	: parameters(parameters),
	  soundProcessor(soundProcessor),
	  soundIds()
	{

		// Only selects the triggers that the instrument uses.
		std::transform(parameters.triggersIds.cbegin(), parameters.triggersIds.cend(), std::back_inserter(triggers),
				[&] (int triggerId) { return trigs.at(triggerId); } );

		return;
	}

	Instrument::~Instrument()
	{

		return;
	}

	/*void Instrument::SetSoundData(std::vector<short>& data, unsigned int duration)
	{

		this->soundData.clear();
		this->soundData.swap(data);
		this->soundDuration = duration;

		return;
	}*/

	// PRIVATE

	/*void Instrument::CreateTriggers()
	{

		TriggerParameters triggerParameters;

		triggerParameters.scanTime = parameters.scanTime;
		triggerParameters.threshold = parameters.threshold;
		triggerParameters.maskTime = parameters.maskTime;


		switch(parameters.instrumentType)
		{

		case InstrumentType::Drum:
			trigger = std::shared_ptr<Trigger>(new DrumTrigger(triggerParameters));
			break;

		default:
			throw -1;
			break;

		}

		return;
	}
	*/




}

