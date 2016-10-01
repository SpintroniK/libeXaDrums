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


		this->metronome = std::shared_ptr<DrumKit::Metronome>(new DrumKit::Metronome(this->alsaParams));

		this->drumModule = std::unique_ptr<DrumKit::Module>(new DrumKit::Module(moduleLoc, this->mixer, this->metronome));

		return;
	}

	eXaDrums::~eXaDrums()
	{

		return;
	}


	void eXaDrums::SelectKit(int id)
	{

		this->drumModule->SelectKit(id);

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

		this->alsa->Stop();
		this->drumModule->Stop();
		isStarted = false;

		return;
	}


	void eXaDrums::GetClickTypeById(int id, char* kitName, int& nameLength) const
	{

		std::string clickType = Util::Enums::ClickTypeToString(Util::Enums::GetClickTypes()[id]);

		CppStringToC(clickType, kitName, nameLength);

		return;
	}


	void eXaDrums::SetInstrumentVolume(int id, int volume)
	{

		float vol = float(volume) / 100.0f;

		drumModule->SetInstrumentVolume(id, vol);

		return;
	}

	int eXaDrums::GetInstrumentVolume(int id) const
	{

		int volume = (int) std::floor( 100.0f * drumModule->GetInstrumentVolume(id));

		return volume;
	}

	void eXaDrums::GetKitNameById(int id, char* kitName, int& nameLength)
	{

		std::string kit = this->drumModule->GetKitNameById(id);

		CppStringToC(kit, kitName, nameLength);

		return;
	}

	void eXaDrums::GetInstrumentName(int id, char* name, int& nameLength)
	{

		std::string inst = this->drumModule->GetInstrumentName(id);

		CppStringToC(inst, name, nameLength);

		return;
	}

	void eXaDrums::CppStringToC(std::string input, char* str, int& length) const
	{

		// Get string's length
		length = input.length();

		// Copy string to char*
		input.copy(str, length);

		return;
	}

}
