/*
 * Cymbal.h
 *
 *  Created on: 13 Dec 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_CYMBAL_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_CYMBAL_H_

#include "../Instrument.h"

namespace DrumKit
{

	class Cymbal: public Instrument
	{

	public:

		Cymbal(InstrumentParameters parameters);
		virtual ~Cymbal();

		virtual int GetSoundId();

	private:



	};

}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_CYMBALS_CYMBAL_H_ */
