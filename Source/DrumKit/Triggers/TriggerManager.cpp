/*
 * TriggerManager.cpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#include "TriggerManager.h"


#include "../../Util/Enums.h"
#include "../../Util/Xml.h"

#include "Curves/CurveType.h"
#include "TriggerLocation.h"

#include <tinyxml2.h>

#include <algorithm>
#include <iostream>


using namespace tinyxml2;
using namespace Util;

namespace DrumKit
{

	std::vector<int> TriggerManager::LoadTriggersIds(const std::string& moduleDir)
	{

		// Set default sensors parameters
		IO::SensorsConfig sensorsConfig;
		sensorsConfig.resolution = 12;
		sensorsConfig.samplingRate = 1000000;
		sensorsConfig.sensorType = IO::SensorType::Hdd;
		sensorsConfig.hddDataFolder = "";

		// Load triggers config with default sensor parameters
		std::vector<TriggerParameters> trigsParams;
		LoadTriggersConfig(moduleDir, sensorsConfig, trigsParams);

		std::vector<int> triggersIds(trigsParams.size());
		std::transform(trigsParams.cbegin(), trigsParams.cend(), triggersIds.begin(), [&](const TriggerParameters& p) { return p.sensorId; });


		return triggersIds;
	}

	void TriggerManager::LoadTriggersConfig(const std::string& moduleDir, const IO::SensorsConfig& sensorsConfig, std::vector<TriggerParameters>& trigsParams)
	{

		trigsParams.clear();

		const std::string file(moduleDir + "triggersConfig.xml");

		XMLDocument doc;

		if(doc.LoadFile(file.data()) != XML_SUCCESS)
		{
			throw -1;
		}

		XMLElement* root = doc.RootElement();

		// Read all triggers
		for(const auto& trigger : XmlElement{root, "Trigger"})
		{
			TriggerParameters trigParams;

			// Get trigger id
			trigger.Attribute("sensorId", trigParams.sensorId);

			// Get trigger type
			trigParams.type = Enums::ToElement<TriggerType>(trigger.Attribute<std::string>("sensorType"));

			// Read xml elements
			trigger.FirstChildElement("Threshold").GetValue(trigParams.threshold);
			trigger.FirstChildElement("ScanTime").GetValue(trigParams.scanTime);
			trigger.FirstChildElement("MaskTime").GetValue(trigParams.maskTime);
			auto response = trigger.FirstChildElement("Response");
			trigParams.response = Enums::ToElement<CurveType>(response.GetValue<std::string>());

			// Sensors configuation
			trigParams.sensorConfig = sensorsConfig;

			trigsParams.push_back(trigParams);
		}


		return;
	}

	void TriggerManager::SaveTriggersConfig(const std::string& moduleDir, const std::vector<TriggerParameters>& trigsParams)
	{

		std::string file(moduleDir + "triggersConfig.xml");

		// Create document
		XMLDocument doc;

		// Add root element
		auto root = doc.NewElement("Triggers");
		doc.InsertFirstChild(root);

		// Add triggers configurations
		for(const auto& trigger : trigsParams)
		{
			std::string sensorTypeStr = Enums::ToString(trigger.type);
			auto trig = CreateXmlElement(doc, "Trigger", "", {{"sensorType", sensorTypeStr}, {"sensorId", trigger.sensorId}});

			trig->InsertEndChild(CreateXmlElement(doc, "Threshold", trigger.threshold));
			trig->InsertEndChild(CreateXmlElement(doc, "ScanTime", trigger.scanTime));
			trig->InsertEndChild(CreateXmlElement(doc, "MaskTime", trigger.maskTime));
			trig->InsertEndChild(CreateXmlElement(doc, "Response", Enums::ToString(trigger.response)));

			root->InsertEndChild(trig);
		}


		// Save file
		doc.SaveFile(file.c_str());

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

		auto root = XmlElement{doc.RootElement()};

		root.FirstChildElement("SamplingRate").GetValue(sensorConfig.samplingRate);
		root.FirstChildElement("Resolution").GetValue(sensorConfig.resolution);
		root.FirstChildElement("HddDataFolder").GetValue(sensorConfig.hddDataFolder);

		auto type = root.FirstChildElement("Type").GetValue<std::string>();
		sensorConfig.sensorType = Enums::ToElement<IO::SensorType>(type);

		return;
	}

	void TriggerManager::SaveSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig)
	{

		std::string file(moduleDir + "sensorsConfig.xml");

		XMLDocument doc;

		// Add root element
		XMLElement* root = doc.NewElement("SensorsConfig");
		doc.InsertFirstChild(root);

		// Create Elements
		XMLElement* samplingRate = doc.NewElement("SamplingRate");
		XMLElement* resolution = doc.NewElement("Resolution");
		XMLElement* type = doc.NewElement("Type");
		XMLElement* dataFolder = doc.NewElement("HddDataFolder");

		samplingRate->SetText(sensorConfig.samplingRate);
		resolution->SetText(sensorConfig.resolution);

		std::string typeStr = Enums::ToString(sensorConfig.sensorType);
		type->SetText(typeStr.c_str());

		dataFolder->SetText(sensorConfig.hddDataFolder.c_str());

		// Add elements to document
		root->InsertEndChild(samplingRate);
		root->InsertEndChild(resolution);
		root->InsertEndChild(type);
		root->InsertEndChild(dataFolder);

		doc.SaveFile(file.c_str());

		return;
	}


} /* namespace DrumKit */

