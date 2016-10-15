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


namespace Util
{


	class Enums
	{

	public:

		// Click type
		static DrumKit::ClickType ClickTypeFromString(const std::string& s);
		static std::string ClickTypeToString(const DrumKit::ClickType& x);
		static std::vector<DrumKit::ClickType> GetClickTypes();

		// Instrument type
		static DrumKit::InstrumentType InstrumentTypeFromString(const std::string& s);
		static std::string InstrumentTypeToString(const DrumKit::InstrumentType& x);
		static std::vector<DrumKit::InstrumentType> GetInstrumentTypes();

		// Trigger type
		static DrumKit::TriggerType TriggerTypeFromString(const std::string& s);
		static std::string TriggerTypeToString(const DrumKit::TriggerType& x);
		static std::vector<DrumKit::TriggerType> GetTriggerTypes();

		// Trigger location
		static DrumKit::TriggerLocation TriggerLocationFromString(const std::string& s);
		static std::string TriggerLocationToString(const DrumKit::TriggerLocation& x);
		static std::vector<DrumKit::TriggerLocation> GetTriggerLocations();

		// Cruves types
		static DrumKit::CurveType CurveTypeFromString(const std::string& s);
		static std::string CurveTypeToString(const DrumKit::CurveType& x);
		static std::vector<DrumKit::CurveType> GetCurveTypes();

		// Sensors types
		static IO::SensorType SensorTypeFromString(const std::string& s);
		static std::string SensorTypeToString(const IO::SensorType& x);
		static std::vector<IO::SensorType> GetSensorTypes();

		// Instrument sound type
		static Sound::InstrumentSoundType InstrumentSoundTypeFromString(const std::string& s);
		static std::string InstrumentSoundTypeToString(const Sound::InstrumentSoundType& x);
		static std::vector<Sound::InstrumentSoundType> GetInstrumentSoundTypes();


	private:

		Enums(){};
		virtual ~Enums(){};


		static const std::vector<DrumKit::ClickType> clickTypes;
		static const std::vector<DrumKit::InstrumentType> instrumentTypes;
		static const std::vector<DrumKit::TriggerType> triggerTypes;
		static const std::vector<DrumKit::TriggerLocation> triggerLocations;
		static const std::vector<DrumKit::CurveType> curveTypes;
		static const std::vector<IO::SensorType> sensorTypes;
		static const std::vector<Sound::InstrumentSoundType> instrumentSoundsTypes;


	};



}


#endif /* SOURCE_UTIL_ENUMS_H_ */
