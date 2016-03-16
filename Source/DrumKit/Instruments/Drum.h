/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_

#include "../../Sound/SoundBank/SoundBank.h"
#include "../../Sound/SoundProcessor/InstrumentSoundType.h"
#include "../../Sound/SoundProcessor/SoundProcessor.h"

#include "../Triggers/Trigger.h"

#include "Instrument.h"

#include <functional>
#include <vector>
#include <string>
#include <memory>

namespace DrumKit
{

	class Drum : public Instrument
	{

	public:

		Drum(InstrumentParameters parameters);
		virtual ~Drum();

		virtual void SetTriggers(std::vector<TriggerPtr> triggers);
		virtual void SetSound(InstrumentSoundInfo const& soundInfo,
								Sound::SoundBank const& soundBank,
								std::shared_ptr<Sound::SoundProcessor> const& soundProcessor);

		virtual bool isTriggerEvent();
		virtual Sound::SoundPtr GetSound();

	private:

		static const int numTriggers = 2;

		TriggerPtr drumHeadTrigger;
		TriggerPtr drumRimTrigger;

		Sound::SoundPtr drumHeadSound;
		Sound::SoundPtr drumRimSound;

	};

}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
