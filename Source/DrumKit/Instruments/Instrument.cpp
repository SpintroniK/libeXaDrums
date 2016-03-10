/*
 * Instrument.cpp
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */


#include "Instrument.h"

namespace DrumKit
{

	Instrument::Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor, std::map<int, TriggerPtr> const& trigs)
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






}

