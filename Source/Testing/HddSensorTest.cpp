/*
 * HddSensorTest.cpp
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#include "HddSensorTest.h"

namespace Testing
{

	void HddSensorTest::RunTest()
	{

		std::string fileLoc("/home/jeremy/Desktop/Prog/RaspiDrums/out.raw");

		IO::HddSensor sensor(fileLoc);

		int N = sensor.GetDataLength();

		for(int i = 0; i < N; i++)
		{

			short value = sensor.GetOutput();
			std::cout << value << std::endl;

		}

		return;
	}


}

