/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrums.h"

namespace eXaDrumsApi
{

	eXaDrums::eXaDrums(const char* dataLocation) : isStarted(false)
	{

		std::string moduleLoc(dataLocation);

		// Load alsa parameters
		AlsaParams alsaParams;
		AlsaParameters::LoadAlsaParameters(moduleLoc + "alsaConfig.xml", alsaParams);

		// Create mixer and alsa
		this->mixer = std::shared_ptr<Mixer>(new Mixer());
		this->alsa = std::unique_ptr<Alsa>(new Alsa(alsaParams, this->mixer));

		// Load metronome parameters
		MetronomeParameters metronomeParams;
		Metronome::LoadConfig(moduleLoc + "metronomeConfig.xml", metronomeParams);
		this->metronome = std::shared_ptr<DrumKit::Metronome>(new DrumKit::Metronome(alsaParams, metronomeParams));

		// Create drum module
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

	// Metronome

	void eXaDrums::GetClickTypeById(int id, char* kitName, int& nameLength) const
	{

		std::string clickType = Util::Enums::ClickTypeToString(Util::Enums::GetClickTypes()[id]);

		CppStringToC(clickType, kitName, nameLength);

		return;
	}

	int eXaDrums::GetClickTypeId() const
	{

		ClickType clickType = metronome->GetClickType();
		const std::vector<ClickType>& clickTypes = Util::Enums::GetClickTypes();

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), clickType);
		int index = std::distance(clickTypes.cbegin(), it);

		return index;
	}


	void eXaDrums::GetRhythmList(int* data) const
	{

		std::vector<int> rhythmList = this->metronome->GetRhythmList();
		std::copy(rhythmList.cbegin(), rhythmList.cend(), data);

		return;
	}

	void eXaDrums::GetBpmeasList(int* data) const
	{

		std::vector<int> bpmeasList = this->metronome->GetBpmeasList();
		std::copy(bpmeasList.cbegin(), bpmeasList.cend(), data);

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
