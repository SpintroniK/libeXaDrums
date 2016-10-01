/*
 * types.hpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_MAPS_HPP_
#define SOURCE_DRUMKIT_KITS_MAPS_HPP_

namespace DrumKit
{


	/*std::map<InstrumentType, std::string> KitManager::instrumentsTypes =
	{
			{InstrumentType::HiHat, 	"HiHat"},
			{InstrumentType::Cymbal, 	"Cymbal"},
			{InstrumentType::BassDrum, 	"BassDrum"},
			{InstrumentType::TestDrum, 	"TestDrum"},
			{InstrumentType::Drum, 		"Drum"}
	};*/

	std::map<TriggerLocation, std::string> KitManager::triggersLocations =
	{
			{TriggerLocation::Rim, 		"Rim"},
			{TriggerLocation::DrumHead,	"DrumHead"}
	};

	std::map<Sound::InstrumentSoundType, std::string>  KitManager::soundsTypes =
	{
			{Sound::InstrumentSoundType::ClosingHiHat, 	"ClosingHiHat"},
			{Sound::InstrumentSoundType::RimShot, 		"RimShot"},
			{Sound::InstrumentSoundType::Default, 		"Default"}
	};

}



#endif /* SOURCE_DRUMKIT_KITS_MAPS_HPP_ */
