/*
 * HddSensorTest.h
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_TESTING_HDDSENSORTEST_H_
#define RASPIDRUMS_SOURCE_TESTING_HDDSENSORTEST_H_

#include "../IO/HddSensor.h"

#include <string>
#include <iostream>

namespace Testing
{

	class HddSensorTest
	{

	public:

		static void RunTest();

	private:

		HddSensorTest() {};
		virtual ~HddSensorTest() {};

	};


}


#endif /* RASPIDRUMS_SOURCE_TESTING_HDDSENSORTEST_H_ */
