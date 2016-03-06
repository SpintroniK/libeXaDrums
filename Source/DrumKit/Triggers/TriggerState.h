/*
 * TriggerState.h
 *
 *  Created on: 6 Mar 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_

#include "TriggerType.h"

namespace DrumKit
{

	struct TriggerState
	{

		int sensorId;
		float strength;
		bool isTrig;
		TriggerType type;


	};



}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_ */
