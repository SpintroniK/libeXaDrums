/*
 * InstrumentParameters.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_


#include "../../IO/SensorType.h"


namespace DrumKit
{

	struct InstrumentParameters
	{

			int id;
			int sensorId;
			IO::SensorType sensorType;

			std::string instrumentName;
			std::string soundFile;

			std::vector<float> curve;

			unsigned int scanTime;
			short threshold;
			int maskTime;

	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_ */
