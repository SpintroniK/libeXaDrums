/*
 * AlsaParameters.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#include "AlsaParameters.h"

#include "../../Util/ErrorHandling.h"

#include <tinyxml2.h>

#include <iostream>

using namespace tinyxml2;
using namespace Util;

namespace Sound
{

	void AlsaParameters::LoadAlsaParameters(const std::string& filePath, AlsaParams& parameters)
	{

		XMLDocument doc;

		if(doc.LoadFile(filePath.c_str()) != XML_SUCCESS)
		{
			throw Exception("Could not load sound card parameters.", error_type_error);
		}

		XMLElement* root = doc.RootElement();

		XMLElement* device = root->FirstChildElement("device");
		XMLElement* capture = root->FirstChildElement("capture");
		XMLElement* format = root->FirstChildElement("format");
		XMLElement* sampleRate = root->FirstChildElement("sampleRate");
		XMLElement* nChannels = root->FirstChildElement("nChannels");
		XMLElement* bufferTime = root->FirstChildElement("bufferTime");
		XMLElement* periodTime = root->FirstChildElement("periodTime");
		XMLElement* access = root->FirstChildElement("access");

		parameters.device = device->GetText();
		parameters.capture = (bool) std::stoi(capture->GetText());
		parameters.format = GetSndFormat(format->GetText());
		parameters.sampleRate = (unsigned int) std::stoi(sampleRate->GetText());
		parameters.nChannels = (unsigned int) std::stoi(nChannels->GetText());
		parameters.bufferTime = (unsigned int) std::stoi(bufferTime->GetText());
		parameters.periodTime = (unsigned int) std::stoi(periodTime->GetText());
		parameters.access = GetAccessType(access->GetText());

		return;
	}

	void AlsaParameters::SaveAlsaParameters(const std::string& filePath, const AlsaParams& parameters)
	{

		// Create document
		XMLDocument doc;

		// Add root element
		XMLElement* root = doc.NewElement("root");
		doc.InsertFirstChild(root);

		// Create Elements
		XMLElement* device = doc.NewElement("device");
		XMLElement* capture = doc.NewElement("capture");
		XMLElement* format = doc.NewElement("format");
		XMLElement* sampleRate = doc.NewElement("sampleRate");
		XMLElement* nChannels = doc.NewElement("nChannels");
		XMLElement* bufferTime = doc.NewElement("bufferTime");
		XMLElement* periodTime = doc.NewElement("periodTime");
		XMLElement* access = doc.NewElement("access");

		// Set values
		device->SetText(parameters.device.data());
		capture->SetText(int(parameters.capture));
		format->SetText("SND_PCM_FORMAT_S16_LE"); // XXX: temporary
		sampleRate->SetText(parameters.sampleRate);
		nChannels->SetText(parameters.nChannels);
		bufferTime->SetText(parameters.bufferTime);
		periodTime->SetText(parameters.periodTime);
		access->SetText("SND_PCM_ACCESS_RW_INTERLEAVED"); // XXX: temporary

		// Insert all elements
		root->InsertEndChild(device);
		root->InsertEndChild(capture);
		root->InsertEndChild(format);
		root->InsertEndChild(sampleRate);
		root->InsertEndChild(nChannels);
		root->InsertEndChild(bufferTime);
		root->InsertEndChild(periodTime);
		root->InsertEndChild(access);

		// Save modified file
		auto result = doc.SaveFile(filePath.data());

		if(XML_SUCCESS != result)
		{
			throw Exception("Could not save triggers configuration.", error_type_error);
		}


		return;
	}

	// PRIVATE

	snd_pcm_format_t AlsaParameters::GetSndFormat(std::string formatName)
	{

		snd_pcm_format_t format;

		std::map<std::string, snd_pcm_format_t> dic;

		// Add definitions to dic
		dic["SND_PCM_FORMAT_S16_LE"] = SND_PCM_FORMAT_S16_LE;

		std::map< std::string, snd_pcm_format_t>::iterator i = dic.find(formatName);

		if(i != dic.end())
			format = i->second;
		else
			format = SND_PCM_FORMAT_S8; // Default value

		return format;
	}

	snd_pcm_access_t AlsaParameters::GetAccessType(std::string accessName)
	{

		snd_pcm_access_t access;

		std::map<std::string, snd_pcm_access_t> dic;

		// Add definitions to dic
		dic["SND_PCM_ACCESS_RW_INTERLEAVED"] = SND_PCM_ACCESS_RW_INTERLEAVED;
		dic["SND_PCM_ACCESS_MMAP_INTERLEAVED"] = SND_PCM_ACCESS_MMAP_INTERLEAVED;

		std::map< std::string, snd_pcm_access_t>::iterator i = dic.find(accessName);

		if(i != dic.end())
			access = i->second;
		else
			access = SND_PCM_ACCESS_RW_INTERLEAVED; // Default value

		return access;

	}



} /* namespace Sound */
