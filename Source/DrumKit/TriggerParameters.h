/*
 * TriggerParameters.h
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERPARAMETERS_H_
#define SOURCE_DRUMKIT_TRIGGERPARAMETERS_H_

#include <vector>

namespace DrumKit
{

	struct TriggerParameters
	{

		int drumId;
		unsigned int scanTime;
		short threshold;
		int maskTime;
		std::vector<float> curve;

	};

}


#endif /* SOURCE_DRUMKIT_TRIGGERPARAMETERS_H_ */
