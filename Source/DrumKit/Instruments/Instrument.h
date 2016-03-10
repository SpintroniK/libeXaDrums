/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_


#include "../../Sound/SoundProcessor/SoundProcessor.h"

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

		Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor, std::map<int, std::shared_ptr<Trigger>> const& trigs);
		virtual ~Instrument();


		virtual int GetSoundProps() = 0;

		virtual std::vector<int> const& GetTriggers() const { return this->parameters.triggersIds; };
		virtual int GetId() const { return this->parameters.id; }


	protected:


		virtual void GenerateSounds() = 0;

		InstrumentParameters parameters;
		std::shared_ptr<Sound::SoundProcessor> soundProcessor;
		std::map<int, int> soundIds;
		std::vector<TriggerPtr> triggers;

	private:



	};

	typedef std::shared_ptr<Instrument> InstrumentPtr;

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
