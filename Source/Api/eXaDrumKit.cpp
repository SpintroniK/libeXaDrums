/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrumKit.h"

namespace eXaDrumKitApi
{

	eXaDrumKit::eXaDrumKit(const char* dataLocation)
	: drumModule(std::string(dataLocation))
	{

		return;
	}

	eXaDrumKit::eXaDrumKit()
	: drumModule(defaultDataLoc)
	{

		return;
	}

	eXaDrumKit::~eXaDrumKit()
	{

		return;
	}

	void eXaDrumKit::LoadKit(const char* kitLocation)
	{

		std::string location(kitLocation);
		std::string moduleLoc;

		this->drumModule.GetDirectory(moduleLoc);

		this->drumModule.LoadKit(moduleLoc + "/" + location, this->kit);



		return;
	}
}
