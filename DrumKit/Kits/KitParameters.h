/*
 * KitParameters.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_KITS_KITPARAMETERS_H
#define LIBEXADRUMS_DRUMKIT_KITS_KITPARAMETERS_H

#include "../Instruments/InstrumentParameters.h"

#include <string>
#include <vector>

namespace DrumKit
{

	struct KitParameters
	{

		KitParameters() noexcept : kitName(), configFilePath(), instrumentParameters() {}

		std::string kitName;
		std::string configFilePath;
		std::vector<InstrumentParameters> instrumentParameters;

	};

}


#endif /* LIBEXADRUMS_DRUMKIT_KITS_KITPARAMETERS_H */
