/*
 * Pad.h
 *
 *  Created on: 11 Jun 2017
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_PADS_PAD_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_PADS_PAD_H_

#include "../../../Sound/SoundBank/SoundBank.h"
#include "../../../Sound/InstrumentSoundType.h"

#include "../../Triggers/Triggers/Trigger.h"

#include "../Instrument.h"

#include <vector>
#include <memory>

namespace DrumKit
{

	class Pad : public Instrument
	{

	public:

		Pad(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
		virtual ~Pad();

		static const std::vector<TriggerLocation> triggersLocations;
		static const std::vector<Sound::InstrumentSoundType> soundsTypes;

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) override;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) override;
		virtual void SetVolume(float volume) override;

		virtual void GetSoundProps(int& id, float& volume) const override;
		virtual bool IsTriggerEvent() const override;

	private:

		TriggerPtr trigger;

		int soundId;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_PADS_PAD_H_ */
