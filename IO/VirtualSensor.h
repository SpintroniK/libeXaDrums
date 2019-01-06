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

namespace IO
{
	class VirtualSensor : public ISensor
	{

	public:

		VirtualSensor() { is_digital = true; }
		virtual ~VirtualSensor() {}

		virtual short GetData(char channel) final
		{
			return data.exchange(0, std::memory_order_acquire);
		}
		virtual void SetData(char channel, short value) final
		{
			data.store(value, std::memory_order_release);
		}

	private:

		std::atomic<short> data{};
	};
}

#endif /* IO_VIRTUALSENSOR_H_ */
