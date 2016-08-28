/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_


#include "../../Sound/SoundProcessor/SoundProcessor.h"
#include "../../Sound/SoundBank/SoundBank.h"
#include "../../Sound/Sound.h"

#include "../Triggers/Trigger.h"

#include "InstrumentParameters.h"

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <utility>

namespace DrumKit
{

	class Instrument
	{

	public:

		Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> sb);
		virtual ~Instrument();


		virtual void SetTriggers(std::vector<TriggerPtr>& triggers) = 0;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo,	std::shared_ptr<Sound::SoundProcessor> const& soundProcessor) = 0;
		virtual void SetVolume(std::shared_ptr<Sound::SoundBank>& soundBank, float volume) = 0;

		virtual void GetSoundProps(int& id, float& volume) = 0;
		virtual bool isTriggerEvent()= 0;

		virtual int GetId() const { return this->parameters.id; }


	protected:

		InstrumentParameters parameters;
		std::shared_ptr<Sound::SoundBank> soundBank;
		//std::map<int, int> soundIds;


	private:



	};

	typedef std::shared_ptr<Instrument> InstrumentPtr;

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
