/*
 * TriggerState.h
 *
 *  Created on: 6 Mar 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_


namespace DrumKit
{

	struct TriggerState
	{

		int sensorId;
		float value;
		bool isTrig;
		int64_t trigTime;

	};



}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERSTATE_H_ */
