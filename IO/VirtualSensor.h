/*
 * ExternalSensor.h
 *
 *  Created on: 6 Jan 2019
 *      Author: jeremy
 */

#ifndef IO_VIRTUALSENSOR_H_
#define IO_VIRTUALSENSOR_H_

#include "ISensor.h"

#include <atomic>
#include <memory>

namespace IO
{
	class VirtualSensor : public ISensor
	{

	public:

		VirtualSensor(size_t chan) 
		{ 
			isDigital = true; 
			channel = chan;
		}
		virtual ~VirtualSensor() = default;

		virtual short GetData() final
		{
			return data.exchange(0, std::memory_order_acquire);
		}
		virtual void SetData(short value) final
		{
			data.store(value, std::memory_order_release);
		}

	private:

		std::atomic<short> data{};
	};

	using VirtualSensorPtr = std::unique_ptr<VirtualSensor>;

}

#endif /* IO_VIRTUALSENSOR_H_ */
