/*
 * AlsaParameters.cpp
 *
 *  Created on: 7 Feb 2016
 *      Author: jeremy
 */

#include "AlsaParameters.h"

#include <tinyxml2.h>


using namespace tinyxml2;

namespace Sound
{

	void AlsaParameters::LoadAlsaParameters(std::string filePath, AlsaParams& parameters)
	{

		XMLDocument doc;

		if(doc.LoadFile(filePath.c_str()) != XML_SUCCESS)
			throw -1;

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
		parameters.capture = (bool) std::atoi(capture->GetText());
		parameters.format = GetSndFormat(format->GetText());
		parameters.sampleRate = (unsigned int) std::atoi(sampleRate->GetText());
		parameters.nChannels = (unsigned int) std::atoi(nChannels->GetText());
		parameters.bufferTime = (unsigned int) std::atoi(bufferTime->GetText());
		parameters.periodTime = (unsigned int) std::atoi(periodTime->GetText());
		parameters.access = GetAccessType(access->GetText());

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

	_snd_pcm_access AlsaParameters::GetAccessType(std::string accessName)
	{

		_snd_pcm_access access;

		std::map<std::string, _snd_pcm_access> dic;

		// Add definitions to dic
		dic["SND_PCM_ACCESS_RW_INTERLEAVED"] = SND_PCM_ACCESS_RW_INTERLEAVED;
		dic["SND_PCM_ACCESS_MMAP_INTERLEAVED"] = SND_PCM_ACCESS_MMAP_INTERLEAVED;

		std::map< std::string, _snd_pcm_access>::iterator i = dic.find(accessName);

		if(i != dic.end())
			access = i->second;
		else
			access = SND_PCM_ACCESS_RW_INTERLEAVED; // Default value

		return access;

	}



} /* namespace Sound */
