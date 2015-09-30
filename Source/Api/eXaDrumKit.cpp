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
	  alsaParams(), triggers()
	{

		std::string moduleLoc;
		this->drumModule.GetDirectory(moduleLoc);

		Sound::Alsa::ReadXmlConfig(this->alsaParams, moduleLoc + "alsaConfig.xml");

		this->mixer = std::unique_ptr<Sound::Mixer>(new Sound::Mixer(this->drumModule.soundParameters, this->alsaParams));

		this->alsa = std::unique_ptr<Sound::Alsa>(new Sound::Alsa(this->alsaParams, *this->mixer));

		return;
	}

	eXaDrumKit::~eXaDrumKit()
	{

		this->triggers.clear();

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

	void eXaDrumKit::Start()
	{

		this->alsa->Start();

		return;
	}

	void eXaDrumKit::Stop()
	{

		this->alsa->Stop();

		return;
	}

	size_t eXaDrumKit::AddTrigger(size_t drumId)
	{

		if(this->kit.drum.size() <= drumId)
			throw -1;

		this->triggers.push_back(std::unique_ptr<DrumKit::Trigger>(new DrumKit::Trigger(this->kit.drum[drumId], *this->mixer)));

		return this->triggers.size();
	}

	void eXaDrumKit::Trig(size_t triggerId, short value)
	{

		if(this->triggers.size() <= triggerId)
			throw -1;

		this->triggers[triggerId]->Trig(value);

		return;
	}
}
