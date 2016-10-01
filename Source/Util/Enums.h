/*
 * Enums.h
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_ENUMS_H_
#define SOURCE_UTIL_ENUMS_H_


#include "../Metronome/ClickTypes.h"
#include "../DrumKit/Instruments/InstrumentType.h"
#include "../DrumKit/Triggers/TriggerType.h"
#include "../DrumKit/Triggers/TriggerLocation.h"
#include "../DrumKit/Triggers/Curves/CurveType.h"
#include "../IO/SensorType.h"
#include "../Sound/InstrumentSoundType.h"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace DrumKit;
using namespace Sound;
using namespace IO;

namespace Util
{


	class Enums
	{

	public:

		// Click type
		static ClickType ClickTypeFromString(const std::string& s);
		static std::string ClickTypeToString(const ClickType& x);
		static std::vector<ClickType> GetClickTypes();

		// Instrument type
		static InstrumentType InstrumentTypeFromString(const std::string& s);
		static std::string InstrumentTypeToString(const InstrumentType& x);
		static std::vector<InstrumentType> GetInstrumentTypes();

		// Trigger type
		static TriggerType TriggerTypeFromString(const std::string& s);
		static std::string TriggerTypeToString(const TriggerType& x);
		static std::vector<TriggerType> GetTriggerTypes();

		// Trigger location
		static TriggerLocation TriggerLocationFromString(const std::string& s);
		static std::string TriggerLocationToString(const TriggerLocation& x);
		static std::vector<TriggerLocation> GetTriggerLocations();

		// Cruves types
		static CurveType CurveTypeFromString(const std::string& s);
		static std::string CurveTypeToString(const CurveType& x);
		static std::vector<CurveType> GetCurveTypes();

		// Sensors types
		static SensorType SensorTypeFromString(const std::string& s);
		static std::string SensorTypeToString(const SensorType& x);
		static std::vector<SensorType> GetSensorTypes();

		// Instrument sound type
		static InstrumentSoundType InstrumentSoundTypeFromString(const std::string& s);
		static std::string InstrumentSoundTypeToString(const InstrumentSoundType& x);
		static std::vector<InstrumentSoundType> GetInstrumentSoundTypes();


	private:

		Enums(){};
		virtual ~Enums(){};


		static const std::vector<ClickType> clickTypes;
		static const std::vector<InstrumentType> instrumentTypes;
		static const std::vector<TriggerType> triggerTypes;
		static const std::vector<TriggerLocation> triggerLocations;
		static const std::vector<CurveType> curveTypes;
		static const std::vector<SensorType> sensorTypes;
		static const std::vector<InstrumentSoundType> instrumentSoundsTypes;


	};



}


#endif /* SOURCE_UTIL_ENUMS_H_ */
