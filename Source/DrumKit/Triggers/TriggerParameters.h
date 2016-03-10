/*
 * TriggerParameters.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_

#include "../../Sound/SoundProcessor/Curves/CurveType.h"
#include "../../IO/SensorType.h"

#include "TriggerType.h"

#include <vector>

namespace DrumKit
{

	struct TriggerParameters
	{

		int sensorId;
		unsigned int scanTime;
		short threshold;
		int maskTime;
		TriggerType type;
		IO::SensorType sensorType;
		Sound::CurveType response;
	};

}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_ */
