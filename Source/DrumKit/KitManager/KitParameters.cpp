/*
 * KitParameters.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#include "../KitManager/KitParameters.h"

using namespace tinyxml2;

namespace DrumKit
{

	void KitParameters::LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams)
	{

		trigsParams.clear();

		std::string file(moduleDir + "triggersConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_NO_ERROR)
			throw -1;

		XMLElement* root = doc.RootElement();

		// Look for first trigger
		XMLElement* firstTrigger = root->FirstChildElement("Trigger");

		// Read all triggers
		for(XMLElement* trigger = firstTrigger; trigger != nullptr; trigger = trigger->NextSiblingElement())
		{
			TriggerParameters trigParams;

			// Get trigger id
			trigParams.sensorId = std::atoi(trigger->Attribute("sensorId"));

			// Get trigger type
			trigParams.type = GetTriggerType(trigger->Attribute("sensorType"));

			// Read xml elements
			XMLElement* threshold = trigger->FirstChildElement("Threshold");
			XMLElement* scanTime = trigger->FirstChildElement("ScanTime");
			XMLElement* maskTime = trigger->FirstChildElement("MaskTime");
			XMLElement* response = trigger->FirstChildElement("Response");

			trigParams.threshold = (short) std::atoi(threshold->GetText());
			trigParams.scanTime = (unsigned int) std::atoi(scanTime->GetText());
			trigParams.maskTime = std::atoi(maskTime->GetText());
			trigParams.response = GetCurveType(response->GetText());

			//XXX Forcing sensor type to HDD (should real from sensor config. file)
			trigParams.sensorType = IO::SensorType::Hdd;

			trigsParams.push_back(trigParams);
		}


		return;
	}


	void KitParameters::LoadKit(std::string file, KitParams& parameters)
	{

		parameters.instrumentParameters.clear();

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_NO_ERROR)
			throw -1;

		XMLElement* root = doc.RootElement();

		XMLElement* kitName = root->FirstChildElement("kitName");
		XMLElement* kitFolder = root->FirstChildElement("kitFolder");

		XMLElement* firstInstrument = root->FirstChildElement("Instrument");

		int instrumentId = 0;

		for(XMLElement* instrument = firstInstrument; instrument != nullptr; instrument = instrument->NextSiblingElement())
		{

			InstrumentParameters instrumentParameters;
			instrumentParameters.triggersIds.clear();

			// Get xml elements
			XMLElement* instrumentName = instrument->FirstChildElement("instrumentName");
			XMLElement* triggers = instrument->FirstChildElement("triggers");
			XMLElement* firstTrigger = triggers->FirstChildElement("trigger");

			// Get triggers
			for(XMLElement* trigger = firstTrigger; trigger != nullptr; trigger = trigger->NextSiblingElement())
			{
				int triggerId = std::atoi(trigger->GetText());
				TriggerLocation triggerLoc = GetTriggerLocation(trigger->Attribute("location"));
				instrumentParameters.triggersIds.push_back(triggerId);
			}


			XMLElement* sounds = instrument->FirstChildElement("sounds");
			XMLElement* firstSound = sounds->FirstChildElement("sound");

			// Get sounds
			int soundId = 0;
			std::vector<InstrumentSoundInfo> soundsInfo;

			for(XMLElement* sound = firstSound; sound != nullptr; sound = sound->NextSiblingElement())
			{

				InstrumentSoundInfo soundInfo;

				soundInfo.id = soundId;
				soundInfo.soundLocation = sound->GetText();
				soundInfo.type = GetSoundType(sound->Attribute("type"));

				soundsInfo.push_back(soundInfo);

				soundId++;

			}

			instrumentParameters.soundsInfo.swap(soundsInfo);

			/*
			XMLElement* threshold = instrument->FirstChildElement("threshold");
			XMLElement* scanTime = instrument->FirstChildElement("scanTime");
			XMLElement* maskTime = instrument->FirstChildElement("maskTime");
			XMLElement* curve = instrument->FirstChildElement("curve");
			*/

			// Populate instrumentParameters
			InstrumentType instrumentType = GetInstrumentType(instrument->Attribute("type"));
			instrumentParameters.instrumentType = instrumentType;
			instrumentParameters.instrumentName = instrumentName->GetText();


			instrumentParameters.id = instrumentId;

			instrumentId++;

			parameters.instrumentParameters.push_back(instrumentParameters);

		}


		parameters.kitName = kitName->GetText();
		parameters.kitFolder = kitFolder->GetText();

		return;
	}


	// PRIVATE

	TriggerType KitParameters::GetTriggerType(std::string type)
	{

		TriggerType triggerType;

		if(type == "Continuous")
		{
			triggerType = TriggerType::Continuous;
		}
		else
		{
			triggerType = TriggerType::Discrete;
		}

		return triggerType;
	}

	TriggerLocation KitParameters::GetTriggerLocation(std::string location)
	{


		TriggerLocation triggerLocation;

		if(location == "Rim")
		{
			triggerLocation = TriggerLocation::Rim;
		}
		else
		{
			triggerLocation = TriggerLocation::DrumHead;
		}

		return triggerLocation;

	}


	Sound::CurveType KitParameters::GetCurveType(std::string type)
	{

		std::map<std::string, Sound::CurveType> dic;

		// Add definitions to dic
		dic["exponential"] = Sound::CurveType::exponential;
		dic["linear"] = Sound::CurveType::linear;

		std::map< std::string, Sound::CurveType>::iterator i = dic.find(type);

		if(i != dic.end())
			return i->second;
		else
			return Sound::CurveType::linear; // Default value
	}

	InstrumentType KitParameters::GetInstrumentType(std::string typeName)
	{


		InstrumentType instrumentType;

		std::map<std::string, InstrumentType> dic;

		// Add definitions to dic
		dic["Drum"] = InstrumentType::Drum;
		dic["Cymbal"] = InstrumentType::Cymbal;
		dic["HiHat"] = InstrumentType::HiHat;
		dic["BassDrum"] = InstrumentType::BassDrum;

		std::map< std::string, InstrumentType>::iterator i = dic.find(typeName);

		if(i != dic.end())
			instrumentType = i->second;
		else
			instrumentType = InstrumentType::Drum; // Default value

		return instrumentType;
	}

	Sound::InstrumentSoundType KitParameters::GetSoundType(std::string type)
	{


		Sound::InstrumentSoundType soundType;

		std::map<std::string, Sound::InstrumentSoundType> dic;

		// Add definitions to dic
		dic["Default"] = Sound::InstrumentSoundType::Default;
		dic["ClosingHiHat"] = Sound::InstrumentSoundType::ClosingHiHat;

		std::map< std::string, Sound::InstrumentSoundType>::iterator i = dic.find(type);

		if(i != dic.end())
			soundType = i->second;
		else
			soundType = Sound::InstrumentSoundType::Default; // Default value

		return soundType;

	}

} /* namespace DrumKit */
