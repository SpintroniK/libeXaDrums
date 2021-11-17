/*
 * TriggerParameters.h
 *
 *  Created on: 14 Mar 2017
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_API_CONFIG_TRIGGERPARAMETERS_API_H
#define LIBEXADRUMS_API_CONFIG_TRIGGERPARAMETERS_API_H


namespace DrumKit { struct TriggerParameters; }

namespace eXaDrumsApi
{

	struct TriggerParameters
	{

		TriggerParameters() noexcept;

		// Conversion to internal type
		explicit TriggerParameters(const DrumKit::TriggerParameters& parameters) noexcept;
		TriggerParameters& operator=(const DrumKit::TriggerParameters& parameters) noexcept;
		explicit operator DrumKit::TriggerParameters() const;

		int sensorId;
		unsigned int scanTime;
		short threshold;
		int maskTime;
		double gain = 1.;

		char type[64];
		char response[64];



	};

}

#endif /* LIBEXADRUMS_API_CONFIG_TRIGGERPARAMETERS_API_H */
