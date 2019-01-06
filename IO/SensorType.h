/*
 * SensorType.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_IO_SENSORTYPE_H_
#define LIBEXADRUMS_SOURCE_IO_SENSORTYPE_H_

#include <sstream>
#include <string>
#include <type_traits>

namespace IO
{

	enum class SensorType
	{
		Virtual,
		Spi,
		UsbSerial,
		Hdd,

		First = Virtual,
		Last = Hdd

	};


	inline std::ostream& operator<<(std::ostream& o, const SensorType& x)
	{

		std::string os;

		switch (x)
		{

		case SensorType::Virtual:	os = "Virtual";		break;
		case SensorType::Spi:		os = "Spi";			break;
		case SensorType::UsbSerial:	os = "UsbSerial";	break;
		case SensorType::Hdd:		os = "Hdd";			break;


		default: break;

		}

		return o << os;
	}


	inline SensorType operator++(SensorType& x) { return x = static_cast<SensorType>(std::underlying_type_t<SensorType>(x) + 1); };
	inline SensorType operator*(SensorType x) { return x; };
	inline SensorType begin(SensorType x) { return SensorType::First; };
	inline SensorType end(SensorType x) { SensorType l = SensorType::Last; return ++l; };


}


#endif /* LIBEXADRUMS_SOURCE_IO_SENSORTYPE_H_ */
