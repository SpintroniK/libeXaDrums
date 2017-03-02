/*
 * TriggerManager.cpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#include "TriggerManager.h"


#include "../../Util/Enums.h"

#include "Curves/CurveType.h"
#include "TriggerLocation.h"

#include <tinyxml2.h>


using namespace tinyxml2;
using namespace Util;

namespace DrumKit
{



	void TriggerManager::LoadTriggersConfig(const std::string& moduleDir, std::vector<TriggerParameters>& trigsParams)
	{

		trigsParams.clear();

		std::string file(moduleDir + "triggersConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
		{
			throw -1;
		}

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
			trigParams.type = Enums<TriggerType>::ToElement(trigger->Attribute("sensorType"));

			// Read xml elements
			XMLElement* threshold = trigger->FirstChildElement("Threshold");
			XMLElement* scanTime = trigger->FirstChildElement("ScanTime");
			XMLElement* maskTime = trigger->FirstChildElement("MaskTime");
			XMLElement* response = trigger->FirstChildElement("Response");

			trigParams.threshold = (short) std::atoi(threshold->GetText());
			trigParams.scanTime = (unsigned int) std::atoi(scanTime->GetText());
			trigParams.maskTime = std::atoi(maskTime->GetText());
			trigParams.response = Enums<CurveType>::ToElement(response->GetText());

			// Retrieve sensor type
			IO::SensorsConfig sensorsConfig;
			LoadSensorsConfig(moduleDir, sensorsConfig);

			trigParams.sensorType = sensorsConfig.sensorType;

			trigsParams.push_back(trigParams);
		}


		return;
	}


	void TriggerManager::LoadSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig)
	{

		std::string file(moduleDir + "sensorsConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
		{
			throw -1;
		}

		XMLElement* root = doc.RootElement();

		XMLElement* samplingRate = root->FirstChildElement("SamplingRate");
		XMLElement* resolution = root->FirstChildElement("Resolution");
		XMLElement* type = root->FirstChildElement("Type");

		sensorConfig.samplingRate = std::stoi(samplingRate->GetText());
		sensorConfig.resolution = std::stoi(resolution->GetText());
		sensorConfig.sensorType = Enums<IO::SensorType>::ToElement(type->GetText());

		return;
	}


} /* namespace DrumKit */
