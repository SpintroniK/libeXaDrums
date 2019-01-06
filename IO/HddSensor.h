/*
 * Sensor.h
 *
 *  Created on: 7 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_
#define RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_


#include "ISensor.h"

#include <string>
#include <vector>

namespace IO
{

	class HddSensor : public ISensor
	{

	public:

		explicit HddSensor(const std::string& filePath);
		virtual ~HddSensor();

		virtual short GetData(char channel) final;
		virtual void SetData(char channel, short value) final {}

	private:

		static const std::vector<std::string> dataFiles;


		void ReadData(char channel);

		std::string path;
		std::vector<short> data;
		unsigned int index;

	};

}

#endif /* RASPIDRUMS_SOURCE_IO_HDDSENSOR_H_ */
