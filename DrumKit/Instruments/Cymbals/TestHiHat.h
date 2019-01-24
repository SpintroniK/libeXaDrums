/*
 * TestHiHat.h
 *
 *  Created on: 2 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_

#include "../../../Sound/SoundBank/SoundBank.h"
#include "../../../Sound/InstrumentSoundType.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <vector>
#include <memory>

#include <cmath>

namespace DrumKit
{

	class TestHiHat: public Instrument
	{

	public:

		TestHiHat(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> soundBank);
		~TestHiHat() = default;

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) final;
		virtual void SetVolume(float volume) final;

		virtual bool IsTriggerEvent() const final;
		virtual void GetSoundProps(int& id, float& volume) const final;

		virtual std::vector<Sound::InstrumentSoundType> GetSoundTypes() const final { return {Sound::InstrumentSoundType::Default}; }
		virtual std::vector<TriggerLocation> GetTriggersLocations() const final { return {TriggerLocation::DrumHead, TriggerLocation::Rim}; };
		virtual std::vector<int> GetTriggersIds() const final { return {cymbalTrigger->GetId(), pedalTrigger->GetId()}; };

	private:


		TriggerPtr cymbalTrigger;
		TriggerPtr pedalTrigger;

		std::vector<int> hiHatSoundsIds;

		int cymbalSoundId;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_ */
