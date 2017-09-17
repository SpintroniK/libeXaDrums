/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_

#include "../../../Sound/SoundBank/SoundBank.h"
#include "../../../Sound/InstrumentSoundType.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <vector>
#include <memory>


namespace DrumKit
{

	class TestDrum : public Instrument
	{

	public:

		TestDrum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
		~TestDrum() = default;

		static const std::vector<TriggerLocation> triggersLocations;
		static const std::vector<Sound::InstrumentSoundType> soundsTypes;

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) final;
		virtual void SetVolume(float volume) final;

		virtual bool IsTriggerEvent() const final;
		virtual void GetSoundProps(int& id, float& volume) const final;

	private:

		TriggerPtr drumHeadTrigger;
		TriggerPtr drumRimTrigger;

		int drumHeadSoundId;
		int drumRimSoundId;

	};

}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
