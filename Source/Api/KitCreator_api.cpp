/*
 * KitCreator.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator_api.h"

#include <algorithm>
#include <memory>


namespace eXaDrumsApi
{

	KitCreator::KitCreator(const char* dataLocation) : controller(*new DrumKit::KitCreator(dataLocation))
	{

		return;
	}

	KitCreator::~KitCreator()
	{

		// Delete controller
		delete &controller;

		return;
	}



	// Private Methods

	void KitCreator::GetTriggersIds_(int* data, unsigned int& size) const
	{

		if(data == nullptr)
		{
			size = controller.GetTriggersIds().size();
			return;
		}

		std::vector<int> trigsIds = controller.GetTriggersIds();
		std::copy(trigsIds.cbegin(), trigsIds.cend(), data);
		size = trigsIds.size();

		return;
	}

	void KitCreator::GetSoundFiles_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetSoundFiles().size();
			return;
		}

		this->soundsFiles.clear();
		this->soundsFiles = controller.GetSoundFiles();

		unsigned int numElements = std::min<unsigned int>(size, soundsFiles.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = soundsFiles[i].c_str();
		}

		return;
	}

	void KitCreator::GetSoundTypes_(const char* instrumentType, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetSoundTypes(std::string(instrumentType)).size();
			return;
		}

		this->soundsTypes.clear();
		this->soundsTypes = controller.GetSoundTypes(std::string(instrumentType));

		unsigned int numElements = std::min<unsigned int>(size, soundsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = soundsTypes[i].c_str();
		}

		return;
	}

	void KitCreator::GetInstrumentsTypes_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentsTypes().size();
			return;
		}

		this->instrumentsTypes.clear();
		this->instrumentsTypes = controller.GetInstrumentsTypes();

		unsigned int numElements = std::min<unsigned int>(size, instrumentsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentsTypes[i].c_str();
		}

		return;
	}

	void KitCreator::GetTriggersLocations_(const char* instrumentType, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetTriggersLocations(std::string(instrumentType)).size();
			return;
		}

		this->triggersLocations.clear();
		this->triggersLocations = controller.GetTriggersLocations(std::string(instrumentType));

		unsigned int numElements = std::min<unsigned int>(size, triggersLocations.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = triggersLocations[i].c_str();
		}

		return;
	}



} /* namespace eXaDrumsApi */
