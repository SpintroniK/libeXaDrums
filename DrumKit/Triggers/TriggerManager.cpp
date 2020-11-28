/*
 * TriggerManager.cpp
 *
 *  Created on: 3 Sep 2016
 *      Author: jeremy
 */

#include "TriggerManager.h"


#include "../../Util/Enums.h"
#include "../../Util/ErrorHandling.h"
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
			throw Exception("Could not load triggers configuration.", error_type_error);
		}

		XMLElement* root = doc.RootElement();

		// Read all triggers
		for(const auto& trigger : XmlElement{root, "Trigger"})
		{
			TriggerParameters trigParams;

			// Get trigger id
			trigger.Attribute("sensorId", trigParams.sensorId);

			// Get trigger type
			trigParams.type = trigger.Attribute<TriggerType>("sensorType");

			// Read xml elements
			auto gainDefined = trigger.FirstChildElement("Gain").GetValue(trigParams.gain);

			if(!gainDefined)
			{
				trigParams.gain = 1.;
			}

			trigger.FirstChildElement("Threshold").GetValue(trigParams.threshold);
			trigger.FirstChildElement("ScanTime").GetValue(trigParams.scanTime);
			trigger.FirstChildElement("MaskTime").GetValue(trigParams.maskTime);
			auto response = trigger.FirstChildElement("Response");
			trigParams.response = response.GetValue<CurveType>();

			// Sensors configuation
			trigParams.sensorConfig = sensorsConfig;

			trigsParams.push_back(trigParams);
		}


		return;
	}

	void TriggerManager::SaveTriggersConfig(const std::string& moduleDir, const std::vector<TriggerParameters>& triggerParameters)
	{

		std::vector<TriggerParameters> trigsParams = triggerParameters;
		std::sort(trigsParams.begin(), trigsParams.end(), [](const auto& t1, const auto& t2) { return t1.sensorId < t2.sensorId; });

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
			trig->InsertEndChild(CreateXmlElement(doc, "Gain", trigger.gain));
			trig->InsertEndChild(CreateXmlElement(doc, "ScanTime", trigger.scanTime));
			trig->InsertEndChild(CreateXmlElement(doc, "MaskTime", trigger.maskTime));
			trig->InsertEndChild(CreateXmlElement(doc, "Response", Enums::ToString(trigger.response)));

			root->InsertEndChild(trig);
		}

		// Save file
		auto result = doc.SaveFile(file.c_str());

		if(XML_SUCCESS != result)
		{
			throw Exception("Could not save triggers configuration.", error_type_error);
		}

		return;
	}

	void TriggerManager::LoadSensorsConfig(const std::string& moduleDir, IO::SensorsConfig& sensorConfig)
	{

		std::string file(moduleDir + "sensorsConfig.xml");

		XMLDocument doc;
		auto ret = doc.LoadFile(file.c_str());
		if(ret != XML_SUCCESS)
		{
			throw Exception("Could not load sensors configuration.", error_type_error);
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

		auto result = doc.SaveFile(file.c_str());

		if(XML_SUCCESS != result)
		{
			throw Exception("Could not save sensors configuration.", error_type_error);
		}

		return;
	}


} /* namespace DrumKit */

