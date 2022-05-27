/*
 * Pad.h
 *
 *  Created on: 11 Jun 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H
#define LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H

#include "../../../Sound/SoundBank/SoundBank.h"
#include "../../../Sound/InstrumentSoundType.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <memory>
#include <vector>

namespace DrumKit
{

	class Pad : public Instrument
	{

	public:

		Pad(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
		~Pad() = default;

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) final;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) final;
		virtual void SetVolume(float volume) final;

		virtual void GetSoundProps(int& id, float& volume) const final;
		virtual bool IsTriggerEvent() const final;

		std::optional<int> GetSoundIdFromMidiParams(uint8_t note) const final;

		virtual std::vector<Sound::InstrumentSoundType> GetSoundTypes() const final { return {Sound::InstrumentSoundType::Default}; }
		virtual std::vector<TriggerLocation> GetTriggersLocations() const final { return {TriggerLocation::DrumHead}; };
		virtual std::vector<int> GetTriggersIds() const final { return { trigger->GetId() }; };

	private:

		Trigger* trigger;

		int soundId;

	};

} /* namespace DrumKit */

#endif /* LIBEXADRUMS_DRUMKIT_INSTRUMENTS_PADS_PAD_H */
