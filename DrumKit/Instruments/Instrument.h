/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_


#include "../../Sound/SoundBank/SoundBank.h"

#include "../Triggers/Triggers/Trigger.h"

#include "InstrumentParameters.h"

#include <vector>
#include <memory>

namespace DrumKit
{

	class Instrument
	{

	public:

		Instrument(const InstrumentParameters& parameters, std::shared_ptr<Sound::SoundBank> sb);

		virtual void SetTriggers(std::vector<TriggerPtr> const& triggers) = 0;
		virtual void SetSound(InstrumentSoundInfo const& soundInfo) = 0;
		virtual void SetVolume(float volume) = 0;

		virtual void GetSoundProps(int& id, float& volume) const = 0;
		virtual bool IsTriggerEvent() const = 0;

		virtual int GetId() const { return this->parameters.id; }
		virtual float GetVolume() const { return this->parameters.volume; }
		virtual std::string GetName() const { return this->parameters.instrumentName; }

		virtual std::vector<Sound::InstrumentSoundType> GetSoundTypes() const = 0;
		virtual std::vector<TriggerLocation> GetTriggersLocations() const = 0;
		virtual std::vector<int> GetTriggersIds() const = 0;

	protected:

		virtual ~Instrument() = default;

		InstrumentParameters parameters;
		std::shared_ptr<Sound::SoundBank> soundBank;
		//std::map<int, int> soundIds;


	private:



	};

	typedef std::shared_ptr<Instrument> InstrumentPtr;

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
