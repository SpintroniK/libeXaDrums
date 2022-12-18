/*
 * Sensor.h
 *
 *  Created on: 25 Oct 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_IO_ISENSOR_H_
#define LIBEXADRUMS_SOURCE_IO_ISENSOR_H_

#include <memory>

namespace IO
{

	class ISensor
	{

	public:

		virtual short GetData() = 0;
		virtual void SetData(short value) = 0;
		virtual bool IsDigital() const { return isDigital; }

		virtual ~ISensor() = default;

	protected:

		bool isDigital{false};
		size_t channel{};

	};

	using ISensorPtr = std::unique_ptr<ISensor>;

} /* namespace IO */

#endif /* LIBEXADRUMS_SOURCE_IO_ISENSOR_H_ */
