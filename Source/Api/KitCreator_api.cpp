/*
 * KitCreator.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator_api.h"


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


	void KitCreator::GetInstrumentTypeById(int id,  char* name, int& length) const
	{

		std::string typeName = controller.GetInstrumentTypeById(id);

		// Get string's length
		length = typeName.length();

		// Copy string to char*
		typeName.copy(name, length);

		return;
	}


} /* namespace eXaDrumsApi */
