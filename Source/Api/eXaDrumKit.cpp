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
	: drumModule(std::string(dataLocation)),
	  alsaParams()
	{

		std::string moduleLoc;
		this->drumModule.GetDirectory(moduleLoc);

		Sound::Alsa::ReadXmlConfig(this->alsaParams, moduleLoc + "alsaConfig.xml");

		this->mixer = new Sound::Mixer(this->drumModule.soundParameters, this->alsaParams);

		this->alsa = new Sound::Alsa(this->alsaParams, *this->mixer);

		return;
	}

	eXaDrumKit::~eXaDrumKit()
	{

		delete this->alsa;
		delete this->mixer;

		return;
	}

	void eXaDrumKit::LoadKit(const char* kitLocation)
	{

		std::string location(kitLocation);
		std::string moduleLoc;

		this->drumModule.GetDirectory(moduleLoc);

		this->drumModule.LoadKit(moduleLoc + location, this->kit);



		return;
	}
}
