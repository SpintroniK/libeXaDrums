/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_


#include "../../Sound/SoundProcessor/SoundProcessor.h"
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

		Instrument(InstrumentParameters parameters);
		virtual ~Instrument();


		virtual void SetTriggers(std::vector<TriggerPtr> triggers) = 0;
		virtual void SetSound(Sound::SoundPtr const& soundPtr, Sound::SoundProcessor const& soundProcessor) = 0;

		virtual Sound::SoundPtr GetSound() = 0;
		virtual bool isTriggerEvent()= 0;

		virtual int GetId() const { return this->parameters.id; }


	protected:

		InstrumentParameters parameters;
		std::map<int, int> soundIds;


	private:



	};

	typedef std::shared_ptr<Instrument> InstrumentPtr;

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
