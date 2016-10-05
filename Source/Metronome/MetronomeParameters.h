/*
 * MetronomeParameters.h
 *
 *  Created on: 5 Oct 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_METRONOMEPARAMETERS_H_
#define SOURCE_METRONOME_METRONOMEPARAMETERS_H_

#include "ClickTypes.h"

namespace DrumKit
{

	struct MetronomeParameters
	{

		MetronomeParameters() : tempo(120), rhythm(2), beatsPerMeasure(4), clickType(ClickType::First) {};

		int tempo;
		int rhythm;
		int beatsPerMeasure;

		ClickType clickType;

	};

}



#endif /* SOURCE_METRONOME_METRONOMEPARAMETERS_H_ */
