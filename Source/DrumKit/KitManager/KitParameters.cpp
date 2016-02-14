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

			// Get xml elements

			XMLElement* instrumentName = instrument->FirstChildElement("instrumentName");
			XMLElement* sensorId = instrument->FirstChildElement("sensorId");
			XMLElement* soundFile = instrument->FirstChildElement("soundFile");
			XMLElement* threshold = instrument->FirstChildElement("threshold");
			XMLElement* scanTime = instrument->FirstChildElement("scanTime");
			XMLElement* maskTime = instrument->FirstChildElement("maskTime");
			XMLElement* curve = instrument->FirstChildElement("curve");

			// Populate instrumentParameters

			InstrumentType instrumentType = GetInstrumentType(instrument->Attribute("type"));
			instrumentParameters.instrumentType = instrumentType;
			instrumentParameters.instrumentName = instrumentName->GetText();
			instrumentParameters.sensorId = std::atoi(sensorId->GetText());
			instrumentParameters.soundFile = soundFile->GetText();
			instrumentParameters.threshold = (short) std::atoi(threshold->GetText());
			instrumentParameters.scanTime = (unsigned int) std::atoi(scanTime->GetText());
			instrumentParameters.maskTime = std::atoi(maskTime->GetText());
			instrumentParameters.curveType = GetCurveType(curve->GetText());

			instrumentParameters.id = instrumentId;

			instrumentId++;

			parameters.instrumentParameters.push_back(instrumentParameters);

		}


		parameters.kitName = kitName->GetText();
		parameters.kitFolder = kitFolder->GetText();

		return;
	}


	// PRIVATE

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


} /* namespace DrumKit */
