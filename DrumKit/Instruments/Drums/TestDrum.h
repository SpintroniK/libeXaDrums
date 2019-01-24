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

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) final;
		virtual void SetVolume(float volume) final;

		virtual bool IsTriggerEvent() const final;
		virtual void GetSoundProps(int& id, float& volume) const final;

		virtual std::vector<Sound::InstrumentSoundType> GetSoundTypes() const final { return {Sound::InstrumentSoundType::Default, Sound::InstrumentSoundType::RimShot}; }
		virtual std::vector<TriggerLocation> GetTriggersLocations() const final { return {TriggerLocation::DrumHead, TriggerLocation::Rim}; };
		virtual std::vector<int> GetTriggersIds() const final { return {drumHeadTrigger->GetId(), drumRimTrigger->GetId()}; };

	private:

		TriggerPtr drumHeadTrigger;
		TriggerPtr drumRimTrigger;

		int drumHeadSoundId;
		int drumRimSoundId;

	};

}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
