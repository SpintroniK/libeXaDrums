/*
 * KitsManager.cpp
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#include "KitManager.h"

using namespace Sound;
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

		return;
	}


	void KitManager::LoadKit(std::string file, KitParameters& parameters)
	{

		parameters.instrumentParameters.clear();

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
		{
			throw -1;
		}

		XMLElement* root = doc.RootElement();

		XMLElement* kitName = root->FirstChildElement("kitName");
		//XMLElement* kitFolder = root->FirstChildElement("kitFolder");

		XMLElement* firstInstrument = root->FirstChildElement("Instrument");

		int instrumentId = 0;

		for(XMLElement* instrument = firstInstrument; instrument != nullptr; instrument = instrument->NextSiblingElement())
		{

			InstrumentParameters instrumentParameters;
			instrumentParameters.triggersIdsAndLocations.clear();

			// Get xml elements
			XMLElement* instrumentName = instrument->FirstChildElement("instrumentName");
			XMLElement* triggers = instrument->FirstChildElement("triggers");
			XMLElement* firstTrigger = triggers->FirstChildElement("trigger");

			// Get triggers
			for(XMLElement* trigger = firstTrigger; trigger != nullptr; trigger = trigger->NextSiblingElement())
			{
				int triggerId = std::atoi(trigger->GetText());
				TriggerLocation triggerLoc = Util::Enums::TriggerLocationFromString(trigger->Attribute("location"));
				instrumentParameters.triggersIdsAndLocations.push_back(std::make_pair(triggerId, triggerLoc));
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
				soundInfo.type = Util::Enums::InstrumentSoundTypeFromString(sound->Attribute("type"));

				soundsInfo.push_back(soundInfo);

				soundId++;

			}

			instrumentParameters.soundsInfo.swap(soundsInfo);

			// Populate instrumentParameters
			InstrumentType instrumentType = Util::Enums::InstrumentTypeFromString(instrument->Attribute("type"));
			instrumentParameters.instrumentType = instrumentType;
			instrumentParameters.instrumentName = instrumentName->GetText();


			instrumentParameters.id = instrumentId;

			// Set volume
			std::string volumeStr = instrument->Attribute("volume");
			instrumentParameters.volume = float(std::atoi(volumeStr.c_str())/100.0f);

			instrumentId++;

			parameters.instrumentParameters.push_back(instrumentParameters);

		}

		parameters.kitName = kitName->GetText();
		//parameters.kitFolder = kitFolder->GetText();

		parameters.configFilePath = file;

		return;
	}


	void KitManager::SaveKit(std::string file, KitParameters parameters)
	{

		// Create document
		XMLDocument doc;

		// Add root element
		XMLElement* root = doc.NewElement("root");
		doc.InsertFirstChild(root);

		// Create Elements
		XMLElement* kitName = doc.NewElement("kitName");
		XMLElement* kitFolder = doc.NewElement("kitFolder");

		// Add values and attributes to elements
		kitName->SetText(parameters.kitName.c_str());
		//kitFolder->SetText(parameters.kitFolder.c_str());

		// Add elements to document
		root->InsertEndChild(kitName);
		root->InsertEndChild(kitFolder);

		// Instruments
		for(InstrumentParameters const& instrumentParameters : parameters.instrumentParameters)
		{
			XMLElement* instrument = doc.NewElement("Instrument");

			// Set type
			std::string instrumentType = Util::Enums::InstrumentTypeToString(instrumentParameters.instrumentType);
			instrument->SetAttribute("type", instrumentType.c_str());

			// Set volume
			int volume = (int)std::floor(instrumentParameters.volume * 100.0f);
			instrument->SetAttribute("volume", volume);

			// Add Instrument name
			XMLElement* instrumentName = doc.NewElement("instrumentName");
			instrumentName->SetText(instrumentParameters.instrumentName.c_str());
			instrument->InsertEndChild(instrumentName);

			// Triggers
			XMLElement* triggers = doc.NewElement("triggers");
			for(auto const& triggerLoc : instrumentParameters.triggersIdsAndLocations)
			{

				XMLElement* trigger = doc.NewElement("trigger");

				// Set location
				std::string location = Util::Enums::TriggerLocationToString(triggerLoc.second);
				trigger->SetAttribute("location", location.c_str());

				// Set id
				trigger->SetText(triggerLoc.first);

				triggers->InsertEndChild(trigger);
			}
			instrument->InsertEndChild(triggers);

			// Sounds
			XMLElement* sounds = doc.NewElement("sounds");
			for(InstrumentSoundInfo const& soundInfo : instrumentParameters.soundsInfo)
			{

				XMLElement* sound = doc.NewElement("sound");

				// Set type
				std::string type = Util::Enums::InstrumentSoundTypeToString(soundInfo.type);
				sound->SetAttribute("type", type.c_str());

				// Set file path
				sound->SetText(soundInfo.soundLocation.c_str());

				// Add sound
				sounds->InsertEndChild(sound);
			}
			instrument->InsertEndChild(sounds);

			// Insert in root
			root->InsertEndChild(instrument);
		}

		// Save file
		doc.SaveFile(file.c_str());

		return;
	}


	bool KitManager::DeleteKit(const int& id)
	{

		const std::string& filePath = filesPaths[id];

		std::ifstream file(filePath.c_str());

		if(file.good())
		{
			unlink(filePath.c_str());
			this->ScanFolder();

			return true;
		}

		return false;
	}


	// PRIVATE METHODS

	void KitManager::ScanFolder()
	{

		this->filesPaths.clear();

		struct dirent* ent;
		DIR* directory = opendir(kitsPath.c_str());

		while((ent = readdir(directory)) != NULL)
		{
			std::string fileName(ent->d_name);
			std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);

			if(fileExtension == "xml")
			{
				this->filesPaths.push_back(this->kitsPath + fileName);
			}
		}

		closedir(directory);

		// Sort
		std::sort(this->filesPaths.begin(), this->filesPaths.end());

		return;
	}


	// PRIVATE




} /* namespace DrumKit */
