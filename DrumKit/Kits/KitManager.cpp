/*
 * KitsManager.cpp
 *
 *  Created on: 8 Nov 2015
 *      Author: jeremy
 */

#include "KitManager.h"

#include "../../Util/ErrorHandling.h"
#include "../../Util/Enums.h"
#include "../../Util/Xml.h"

#include "../Instruments/InstrumentType.h"
#include "../Instruments/InstrumentSoundInfo.h"
#include "../Triggers/TriggerLocation.h"

#include <tinyxml2.h>

#include <algorithm>
#include <iostream>
#include <fstream>

#include <cmath>
#include <cctype>

#include <unistd.h>

#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

using namespace Sound;
using namespace tinyxml2;
using namespace Util;

namespace DrumKit
{

	KitManager::KitManager(const std::string& kitsPath) : kitsPath(kitsPath)
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
			throw Exception("Could not read the drum kit configuration file.", error_type_error);
			return;
		}

		XMLElement* root = doc.RootElement();
		XMLElement* kitName = root->FirstChildElement("kitName");
		parameters.kitName = kitName->GetText();
		//parameters.kitFolder = kitFolder->GetText();

		int instrumentId = 0;
		for(const auto& instrument : XmlElement{root, "Instrument"})
		{
			InstrumentParameters instrumentParameters;
			instrumentParameters.instrumentName = instrument.FirstChildElement("instrumentName").GetText();

			for(const auto& trigger : XmlElement{instrument.FirstChildElement("triggers")})
			{
				int id = std::stoi(trigger.GetText());
				TriggerLocation location = trigger.Attribute<TriggerLocation>("location");

				instrumentParameters.triggersIdsAndLocations.emplace_back(id, location);
			}

			int soundId = 0;
			for(const auto& sound : XmlElement{instrument.FirstChildElement("sounds")})
			{
				InstrumentSoundInfo soundInfo;

				soundInfo.id = soundId;

				auto soundText = sound.GetText();
				
				if(soundText != nullptr)
				{
					soundInfo.soundLocation = soundText;
				}
				else
				{
					throw Exception("Sound location is empty.", error_type_error);
					return;
				}

				sound.Attribute("type", soundInfo.type);

				instrumentParameters.soundsInfo.push_back(soundInfo);

				soundId++;
			}

			// Populate instrumentParameters
			instrument.Attribute("type", instrumentParameters.instrumentType);
			instrumentParameters.id = instrumentId;

			// Instrument volume
			std::string volumeStr = instrument.Attribute<std::string>("volume");
			instrumentParameters.volume = float(std::stoi(volumeStr)/100.0f);

			parameters.instrumentParameters.push_back(instrumentParameters);
			instrumentId++;
		}

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
			std::string instrumentType = Enums::ToString(instrumentParameters.instrumentType);
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
				std::string location = Enums::ToString(triggerLoc.second);
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
				std::string type = Enums::ToString(soundInfo.type);
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
		auto result = doc.SaveFile(file.c_str());

		if(XML_SUCCESS != result)
		{
			throw Exception("Could not save drum kit parameters.", error_type_error);
		}


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

		for(const auto& p: fs::recursive_directory_iterator(kitsPath))
		{
			if(p.path().extension() == ".xml")
			{
				this->filesPaths.push_back(p.path().string());
			}
		}

		// Sort (had to be improved to take capital letters into account)
		std::sort(filesPaths.begin(), filesPaths.end(), [](const std::string& lhs, const std::string& rhs)
		{
			const auto result = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), [](const char& lhs, const char& rhs){return std::tolower(lhs) == std::tolower(rhs);});
			return result.second != rhs.cend() && (result.first == lhs.cend() || std::tolower(*result.first) < std::tolower(*result.second));
		});

		//std::sort(this->filesPaths.begin(), this->filesPaths.end());

		return;
	}


	// PRIVATE




} /* namespace DrumKit */
