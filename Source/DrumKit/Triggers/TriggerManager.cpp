/*
 * TriggerManager.cpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#include "TriggerManager.h"


using namespace tinyxml2;

namespace DrumKit
{

	TriggerManager::TriggerManager()
	{


		return;
	}

	TriggerManager::~TriggerManager()
	{

		return;
	}

	void TriggerManager::LoadTriggersConfig(std::string moduleDir, std::vector<TriggerParameters>& trigsParams)
	{

		trigsParams.clear();

		std::string file(moduleDir + "triggersConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.c_str()) != XML_SUCCESS)
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

	// PRIVATE METHODS

	TriggerType TriggerManager::GetTriggerType(std::string type)
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


	CurveType TriggerManager::GetCurveType(std::string type)
	{

		CurveType curveType;

		// Add definitions to dic
		if(type == "exponential")
		{
			curveType = CurveType::exponential;
		}
		else
		{
			curveType = CurveType::linear;
		}

		return curveType;
	}


} /* namespace DrumKit */
