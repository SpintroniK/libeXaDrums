/*
 * DrumKit.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_TESTING_DRUMKIT_HDDTEST_H_
#define RASPIDRUMS_SOURCE_TESTING_DRUMKIT_HDDTEST_H_

#include "../IO/HddSensor.h"
#include "../DrumKit/Module.h"
#include "../DrumKit/Trigger.h"
#include "../Sound/Alsa.h"
#include "../Sound/Mixer.h"

#include <string>

namespace Testing
{

	class DrumKit_HddTest
	{

	public:

		static void RunTest();

	private:

		DrumKit_HddTest() {};
		virtual ~DrumKit_HddTest() {};

	};


}



#endif /* RASPIDRUMS_SOURCE_TESTING_DRUMKIT_HDDTEST_H_ */
