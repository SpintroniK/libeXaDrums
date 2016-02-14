/*
 * InstrumentParameters.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_


#include "../../Sound/SoundProcessor/Curves/CurveType.h"
#include "../../IO/SensorType.h"

#include "InstrumentType.h"

#include <vector>
#include <string>

namespace DrumKit
{

	struct InstrumentParameters
	{

		InstrumentType instrumentType;

		int id;
		int sensorId;
		IO::SensorType sensorType;

		std::string instrumentName;
		std::string soundFile;

		Sound::CurveType curveType;

		unsigned int scanTime;
		short threshold;
		int maskTime;

	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_ */
