/*
 * TestHiHat.h
 *
 *  Created on: 2 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_

#include "../../../Sound/SoundBank/SoundBank.h"

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
		virtual ~TestHiHat();

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers);
		virtual void SetSound(InstrumentSoundInfo const& soundInfo);
		virtual void SetVolume(float volume);

		virtual bool IsTriggerEvent() const;
		virtual void GetSoundProps(int& id, float& volume) const;

	private:

		static const int numTriggers = 2;

		TriggerPtr cymbalTrigger;
		TriggerPtr pedalTrigger;

		std::vector<int> hiHatSoundsIds;

		int cymbalSoundId;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_TESTHIHAT_H_ */
