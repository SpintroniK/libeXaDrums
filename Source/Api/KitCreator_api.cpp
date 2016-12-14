/*
 * KitCreator.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator_api.h"

#include <algorithm>

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

	void KitCreator::GetSoundTypeById(const char* type, int id, char* soundType, int& length) const
	{

		std::string instrumentType(type);
		std::string soundTypeStr =  controller.GetSoundTypeById(instrumentType, id);

		length = soundTypeStr.length();
		soundTypeStr.copy(soundType, length);

		return;
	}

	void KitCreator::GetTriggerTypeById(const char* type, int id, char* triggerType, int& length) const
	{

		std::string instrumentType(type);
		std::string triggerTypeStr = controller.GetTriggerTypeById(instrumentType, id);

		length = triggerTypeStr.length();
		triggerTypeStr.copy(triggerType, length);

		return;
	}


	void KitCreator::GetInstrumentTypeById(int id,  char* name, int& length) const
	{

		std::string typeName = controller.GetInstrumentTypeById(id);

		// Get string's length
		length = typeName.length();

		// Copy string to char*
		typeName.copy(name, length);

		return;
	}

	void KitCreator::GetSoundFileById(int id, char* name, int& length) const
	{

		std::string fileName = controller.GetSoundFileById(id);

		length = fileName.length();
		fileName.copy(name, length);

		return;
	}

	// Private Methods

	void KitCreator::GetTriggersIds_(int* data, int& size) const
	{

		if(data == nullptr)
		{
			size = (int) controller.GetTriggersIds().size();
			return;
		}

		std::vector<int> trigsIds = controller.GetTriggersIds();
		std::copy(trigsIds.cbegin(), trigsIds.cend(), data);
		size = trigsIds.size();

		return;
	}


} /* namespace eXaDrumsApi */
