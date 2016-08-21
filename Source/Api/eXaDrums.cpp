/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrums.h"

namespace eXaDrumsApi
{

	eXaDrums::eXaDrums(const char* dataLocation)
	: drumModule(nullptr),
	  alsaParams(),
	  alsa(nullptr),
	  mixer(nullptr),
	  isStarted(false)
	{

		std::string moduleLoc(dataLocation);

		Sound::AlsaParameters::LoadAlsaParameters(moduleLoc + "alsaConfig.xml", this->alsaParams);

		this->mixer = std::shared_ptr<Sound::Mixer>(new Sound::Mixer());
		this->alsa = std::unique_ptr<Sound::Alsa>(new Sound::Alsa(this->alsaParams, this->mixer));

		this->drumModule = std::unique_ptr<DrumKit::Module>(new DrumKit::Module(moduleLoc, this->mixer));


		return;
	}

	eXaDrums::~eXaDrums()
	{

		return;
	}


	void eXaDrums::LoadKit(int id)
	{

		this->drumModule->LoadKit(id);

		return;
	}

	void eXaDrums::Start()
	{

		this->alsa->Start();
		this->drumModule->Start();
		isStarted = true;

		return;
	}

	void eXaDrums::Stop()
	{

		this->drumModule->Stop();
		this->alsa->Stop();
		isStarted = false;

		return;
	}

	void eXaDrums::GetKitNameById(int id, char* kitName, int& nameLength)
	{

		std::string kit = this->drumModule->GetKitNameById(id);

		// Get string's length
		nameLength = kit.length();

		// Copy string to char*
		kit.copy(kitName, nameLength);

		return;
	}

}
