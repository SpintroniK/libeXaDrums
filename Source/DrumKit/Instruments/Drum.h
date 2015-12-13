/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_

#include "Instrument.h"

namespace DrumKit
{

	class Drum : public Instrument
	{

	public:

		Drum(InstrumentParameters parameters);

		virtual bool Trig(float& strength);

		~Drum();

	private:



	};



}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_DRUM_H_ */
