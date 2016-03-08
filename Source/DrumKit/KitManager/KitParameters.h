/*
 * KitParameters.h
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_
#define SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_

#include "../../Sound/SoundProcessor/Curves/CurveType.h"
#include "../../Sound/SoundProcessor/InstrumentSoundType.h"

#include "../../IO/SensorType.h"

#include "../Instruments/InstrumentType.h"
#include "../Instruments/InstrumentSoundInfo.h"
#include "../Triggers/TriggerType.h"
#include "../Triggers/TriggerParameters.h"
#include "../Triggers/TriggerLocation.h"

#include "KitParams.h"

#include <tinyxml2.h>

#include <map>

namespace DrumKit
{

	class KitParameters
	{

	public:

		static void LoadKit(std::string file, KitParams& parameters);
		static void LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams);


	private:

		KitParameters() {};
		virtual ~KitParameters() {};

		static TriggerType GetTriggerType(std::string type);
		static TriggerLocation GetTriggerLocation(std::string location);
		static InstrumentType GetInstrumentType(std::string type);
		static Sound::CurveType GetCurveType(std::string type);
		static Sound::InstrumentSoundType GetSoundType(std::string type);

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITMANAGER_KITPARAMETERS_H_ */
