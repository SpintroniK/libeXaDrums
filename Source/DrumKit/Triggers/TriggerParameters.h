/*
 * TriggerParameters.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_

#include "../../IO/SensorsConfig.h"

#include "Curves/CurveType.h"
#include "TriggerType.h"


namespace DrumKit
{

	struct TriggerParameters
	{

		int sensorId;
		int scanTime;
		short threshold;
		int maskTime;

		TriggerType type;
		CurveType response;

		IO::SensorsConfig sensorConfig;
	};

}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERPARAMETERS_H_ */
