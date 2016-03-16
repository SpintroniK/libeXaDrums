/*
 * InstrumentParameters.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_

#include "../Triggers/TriggerLocation.h"

#include "InstrumentSoundInfo.h"
#include "InstrumentType.h"

#include <vector>
#include <string>
#include <utility>

namespace DrumKit
{

	struct InstrumentParameters
	{

		InstrumentType instrumentType;

		int id;

		std::string instrumentName;
		std::vector<InstrumentSoundInfo> soundsInfo;
		std::vector<std::pair<int, TriggerLocation>> triggersIdsAndLocations;

	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_ */
