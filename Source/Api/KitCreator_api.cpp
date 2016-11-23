/*
 * KitCreator.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator_api.h"

#include <string>

namespace eXaDrumsApi
{

	KitCreator::KitCreator(const char* dataLocation) : controller(*new DrumKit::KitCreator(dataLocation))
	{



		return;
	}

	KitCreator::~KitCreator()
	{

		return;
	}

} /* namespace eXaDrumsApi */
