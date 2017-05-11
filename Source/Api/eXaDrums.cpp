/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrums.h"

#include "../DrumKit/DrumModule/Module.h"
#include "../Metronome/Metronome.h"
#include "../Sound/Alsa/Alsa.h"
#include "../Sound/Alsa/AlsaParameters.h"
#include "../Sound/Mixer/Mixer.h"
#include "../Util/Enums.h"

#include <vector>
#include <algorithm>


using namespace Sound;
using namespace DrumKit;
using namespace Util;

namespace eXaDrumsApi
{

	const std::string eXaDrums::metronomeConfigFile = "metronomeConfig.xml";
	const std::string eXaDrums::alsaConfigFile = "alsaConfig.xml";

	eXaDrums::eXaDrums(const char* dataLoc) : dataLocation(dataLoc), isStarted(false)
	{


		// Load alsa parameters
		AlsaParams alsaParams;
		AlsaParameters::LoadAlsaParameters(dataLocation + alsaConfigFile, alsaParams);

		// Create mixer and alsa
		this->mixer = std::make_shared<Mixer>();
		this->alsa = std::unique_ptr<Alsa>(new Alsa(alsaParams, this->mixer));

		// Load metronome parameters
		MetronomeParameters metronomeParams;
		Metronome::LoadConfig(dataLocation + metronomeConfigFile, metronomeParams);
		this->metronome = std::make_shared<Metronome>(alsaParams, metronomeParams);

		// Create drum module
		this->drumModule = std::unique_ptr<Module>(new Module(dataLocation, this->mixer, this->metronome));

		return;
	}

	eXaDrums::~eXaDrums()
	{

		return;
	}

	// Module

	void eXaDrums::Start()
	{

		this->alsa->Start();
		this->drumModule->Start();
		isStarted.store(true);

		return;
	}

	void eXaDrums::Stop()
	{

		this->alsa->Stop();
		this->drumModule->Stop();
		isStarted.store(false);

		return;
	}

	// Metronome

	void eXaDrums::EnableMetronome(bool enable) const
	{
		drumModule->EnableMetronome(enable);
		return;
	}

	void eXaDrums::RestartMetronome() const
	{
		drumModule->RestartMetronome();
		return;
	}

	void eXaDrums::ChangeTempo(int tempo) const
	{
		drumModule->ChangeTempo(tempo);
		return;
	}

	void eXaDrums::ChangeVolume(int volume) const
	{
		drumModule->ChangeVolume(volume);
		return;
	}

	int eXaDrums::GetTempo() const
	{
		return metronome->GetTempo();
	}

	int eXaDrums::GetClickVolume() const
	{
		return int(drumModule->GetClickVolume() * 100.0f);
	}

	void eXaDrums::SaveMetronomeConfig() const
	{
		metronome->SaveConfig(dataLocation + metronomeConfigFile, metronome->GetParameters());
		return;
	}


	void eXaDrums::SetClickType(int id)
	{

		ClickType type = Enums<ClickType>::GetEnumVector()[id];
		metronome->SetClickType(type);

		 return;
	}

	int eXaDrums::GetClickTypeId() const
	{

		ClickType clickType = metronome->GetClickType();
		const std::vector<ClickType>& clickTypes = Enums<ClickType>::GetEnumVector();

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), clickType);
		int index = std::distance(clickTypes.cbegin(), it);

		return index;
	}

	int eXaDrums::GetRhythm() const
	{
		return this->metronome->GetRhythm();
	}

	void eXaDrums::SetRhythm(int rhythm)
	{
		this->metronome->SetRhythm(rhythm);
	}

	int eXaDrums::GetBpmeas() const
	{
		return this->metronome->GetBpmeas();
	}

	void eXaDrums::SetBpmeas(int bpmeas)
	{
		this->metronome->SetBpmeas(bpmeas);
		return;
	}

	void eXaDrums::SelectKit(int id)
	{

		this->drumModule->SelectKit(id);

		return;
	}

	void eXaDrums::SaveKitConfig(int id) const
	{
		drumModule->SaveKitConfig(id);
		return;
	}

	bool eXaDrums::DeleteKit(const int& id)
	{
		return drumModule->DeleteKit(id);
	}

	void eXaDrums::ReloadKits()
	{

		drumModule->ReloadKits();

		return;
	}

	int eXaDrums::GetNumKits() const
	{
		return drumModule->GetNumKits();
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

	long long eXaDrums::GetLastTrigTime() const
	{
		return drumModule->GetLastTrigTime();
	}

	int eXaDrums::GetLastTrigValue() const
	{
		return drumModule->GetLastTrigValue();
	}


	// Private Methods

	const char* eXaDrums::GetDataLocation_() const
	{
		return this->dataLocation.c_str();
	}

	const char* eXaDrums::GetKitDataFileName_()
	{

		std::string kitLocation = this->drumModule->GetKitLocation();
		std::size_t pos = kitLocation.find_last_of("/");

		this->kitDataFileName = kitLocation.substr(pos + 1, std::string::npos);

		return this->kitDataFileName.c_str();
	}

	void eXaDrums::GetClicksTypes_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = Enums<ClickType>::GetEnumVector().size();
			return;
		}

		this->clicksTypes.clear();
		{
			std::vector<ClickType> types = Enums<ClickType>::GetEnumVector();
			std::transform(types.cbegin(), types.cend(), std::back_inserter(clicksTypes), [](const ClickType& t) { return Enums<ClickType>::ToString(t); });
		}

		unsigned int numElements = std::min<unsigned int>(size, clicksTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = clicksTypes[i].c_str();
		}

		return;
	}

	void eXaDrums::GetRhythms_(int* data, unsigned int& size) const
	{

		if(data == nullptr)
		{
			size = this->metronome->GetRhythmList().size();
			return;
		}

		std::vector<int> rhythms = this->metronome->GetRhythmList();
		std::copy(rhythms.cbegin(), rhythms.cend(), data);
		size = rhythms.size();

		return;
	}

	void eXaDrums::GetBpms_(int* data, unsigned int& size) const
	{

		if(data == nullptr)
		{
			size = this->metronome->GetBpmeasList().size();
			return;
		}

		std::vector<int> bpms = this->metronome->GetBpmeasList();
		std::copy(bpms.cbegin(), bpms.cend(), data);
		size = bpms.size();

		return;
	}


	void eXaDrums::GetKitsNames_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = drumModule->GetKitsNames().size();
			return;
		}

		this->kitsNames.clear();
		this->kitsNames = drumModule->GetKitsNames();

		unsigned int numElements = std::min<unsigned int>(size, kitsNames.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = kitsNames[i].c_str();
		}

		return;
	}

	void eXaDrums::GetInstrumentsNames_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = drumModule->GetInstrumentsNames().size();
			return;
		}

		this->instrumentsNames.clear();
		this->instrumentsNames = drumModule->GetInstrumentsNames();

		unsigned int numElements = std::min<unsigned int>(size, instrumentsNames.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentsNames[i].c_str();
		}

		return;
	}

	double eXaDrums::GetClickPosition() const
	{
		return drumModule->GetClickPosition();
	}

}


