/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrums.h"

namespace eXaDrumsApi
{

	eXaDrums::eXaDrums(const char* dataLocation, IO::SensorType sensorType)
	: drumModule(nullptr), alsaParams()
	{

		std::string moduleLoc(dataLocation);

		Sound::Alsa::ReadXmlConfig(this->alsaParams, moduleLoc + "alsaConfig.xml");

		this->mixer = std::shared_ptr<Sound::Mixer>(new Sound::Mixer());
		this->alsa = std::unique_ptr<Sound::Alsa>(new Sound::Alsa(this->alsaParams, this->mixer));

		this->drumModule = std::unique_ptr<DrumKit::Module>(new DrumKit::Module(moduleLoc, sensorType, this->mixer));


		return;
	}

	eXaDrums::~eXaDrums()
	{

		return;
	}

	void eXaDrums::LoadKit(const char* kitLocation)
	{

		std::string location(kitLocation);
		std::string moduleLoc;

		this->drumModule->GetDirectory(moduleLoc);

		this->drumModule->LoadKit(moduleLoc + location, this->kit);

		this->mixer->SetSoundParameters(this->drumModule->soundParameters);

		return;
	}

	void eXaDrums::Start()
	{

		this->alsa->Start();
		this->drumModule->Start();

		return;
	}

	void eXaDrums::Stop()
	{

		this->drumModule->Stop();
		this->alsa->Stop();

		return;
	}

}
