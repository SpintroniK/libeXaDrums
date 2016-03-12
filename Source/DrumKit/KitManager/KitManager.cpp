/*
 * KitsManager.cpp
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#include "KitManager.h"

using namespace tinyxml2;


namespace DrumKit
{

	KitManager::KitManager(std::string kitsPath) : kitsPath(kitsPath)
	{

		this->ScanFolder();

		return;
	}

	KitManager::~KitManager()
	{

		this->filesList.clear();

		return;
	}

	void KitManager::LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams)
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

	void KitManager::LoadKit(std::string file, KitParams& parameters)
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

	// PRIVATE METHODS

	void KitManager::ScanFolder()
	{

		struct dirent* ent;
		DIR* directory = opendir(kitsPath.c_str());

		while((ent = readdir(directory)) != NULL)
		{
			std::string fileName(ent->d_name);
			std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);

			if(fileExtension == "xml")
			{
				this->filesList.push_back(this->kitsPath + fileName);
			}
		}

		return;
	}


	// PRIVATE

	TriggerType KitManager::GetTriggerType(std::string type)
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

	TriggerLocation KitManager::GetTriggerLocation(std::string location)
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


	Sound::CurveType KitManager::GetCurveType(std::string type)
	{

		Sound::CurveType curveType;

		// Add definitions to dic
		if(type == "exponential")
		{
			curveType = Sound::CurveType::exponential;
		}
		else
		{
			curveType = Sound::CurveType::linear;
		}

		return curveType;
	}

	InstrumentType KitManager::GetInstrumentType(std::string typeName)
	{


		InstrumentType instrumentType;

		if(typeName == "HiHat")
		{
			instrumentType= InstrumentType::HiHat;
		}
		else if(typeName == "Cymbal")
		{
			instrumentType = InstrumentType::Cymbal;
		}
		else if(typeName == "HiHat")
		{
			instrumentType = InstrumentType::HiHat;
		}
		else if (typeName == "BassDrum")
		{
			instrumentType = InstrumentType::BassDrum;
		}
		else
		{
			instrumentType = InstrumentType::Drum;
		}


		return instrumentType;
	}

	Sound::InstrumentSoundType KitManager::GetSoundType(std::string type)
	{

		Sound::InstrumentSoundType soundType;

		if(type == "ClosingHiHat")
		{
			soundType = Sound::InstrumentSoundType::ClosingHiHat;
		}
		else
		{
			soundType = Sound::InstrumentSoundType::Default;
		}


		return soundType;

	}


} /* namespace DrumKit */
