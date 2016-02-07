/*
 * KitParameters.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_
#define SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_

#include "../Instruments/InstrumentType.h"
#include "KitParams.h"

#include <tinyxml2.h>

#include <map>

namespace DrumKit
{

	class KitParameters
	{

	public:

		static void LoadKit(std::string file, KitParams& parameters);

	private:

		KitParameters() {};
		virtual ~KitParameters() {};

		static InstrumentType GetInstrumentType(std::string type);

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_ */
