/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_

#include "../../Sound/Mixer.h"
#include "../../Sound/SoundProcessor/SoundProcessor.h"

//#include "../Triggers/DrumTrigger.h"

#include "InstrumentParameters.h"

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <utility>

namespace DrumKit
{

	class Instrument
	{

	public:

		Instrument(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor);
		virtual ~Instrument();

		//virtual bool Trig(float& strength) = 0;
		virtual int GetSoundProps() const = 0;

		//virtual void SetSoundData(std::vector<short>& data, unsigned int duration);


		//virtual std::vector<short> GetSoundData() const { return soundData; };
		//virtual unsigned int GetSoundDuration() const { return soundDuration; };

		//virtual std::string GetSoundFile() const { return this->parameters.soundFile; }

		virtual std::vector<int> const& GetTriggers() const { return this->parameters.triggersIds; };
		virtual int GetId() const { return this->parameters.id; }


	protected:


		virtual void GenerateSounds() = 0;

		InstrumentParameters parameters;
		std::shared_ptr<Sound::SoundProcessor> soundProcessor;
		std::map<int, int> soundIds;

		//std::shared_ptr<IO::ISensor> sensor;
		//std::shared_ptr<Trigger> trigger;

	private:

		//virtual void CreateTriggers();


	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
