/*
 * IInstrument.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_

#include "../../IO/SensorType.h"
#include "../../IO/ISensor.h"
#include "../../IO/HddSensor.h"
#include "../../IO/SpiSensor.h"
#include "../../Sound/Mixer.h"
#include "../../Sound/SoundProcessor/InstrumentSound.h"

#include "../Triggers/DrumTrigger.h"

#include "InstrumentParameters.h"

#include <vector>
#include <string>
#include <memory>


namespace DrumKit
{

	class Instrument
	{

	public:

		Instrument(InstrumentParameters parameters);
		virtual ~Instrument();

		virtual bool Trig(float& strength) = 0;
		virtual int GetSoundId() = 0;
		virtual void GenerateSounds() = 0;

		//virtual void SetSoundData(std::vector<short>& data, unsigned int duration);


		//virtual std::vector<short> GetSoundData() const { return soundData; };
		//virtual unsigned int GetSoundDuration() const { return soundDuration; };

		//virtual std::string GetSoundFile() const { return this->parameters.soundFile; }

		virtual int GetId() const { return this->parameters.id; }


	protected:

		std::vector<Sound::InstrumentSound> sounds;

		InstrumentParameters parameters;
		std::shared_ptr<IO::ISensor> sensor;
		std::shared_ptr<Trigger> trigger;

	private:

		virtual void CreateTrigger();


	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENT_H_ */
