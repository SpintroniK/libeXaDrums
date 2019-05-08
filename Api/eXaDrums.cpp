/*
 * eXaDrumsApi.cpp
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#include "eXaDrums.h"

#include "../Util/ErrorHandling.h"
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

/**
 * eXaDrums API namespace
 */
namespace eXaDrumsApi
{

	const std::string eXaDrums::metronomeConfigFile = "metronomeConfig.xml";
	const std::string eXaDrums::alsaConfigFile = "alsaConfig.xml";

	/**
	 * Create an instance of a drum module
	 * @param dataLoc Path to the configuration files
	 */
	eXaDrums::eXaDrums(const char* dataLoc) : isStarted(false)
	{

		this->dataLocation = std::string{dataLoc} + "/";

		// Load alsa parameters
		AlsaParams alsaParams;
		AlsaParameters::LoadAlsaParameters(dataLocation + alsaConfigFile, alsaParams);

		// Create mixer and alsa
		this->mixer = std::make_shared<Mixer>();
		this->alsa = std::make_unique<Alsa>(alsaParams, this->mixer);

		// Load metronome parameters
		MetronomeParameters metronomeParams;
		Metronome::LoadConfig(dataLocation + metronomeConfigFile, metronomeParams);
		this->metronome = std::make_shared<Metronome>(alsaParams, metronomeParams);

		// Create drum module
		this->drumModule = std::make_unique<Module>(dataLocation, alsaParams, this->mixer, this->metronome);

		return;
	}

	eXaDrums::~eXaDrums()
	{

		return;
	}

	// Module

	error eXaDrums::Start()
	{

		try
		{
			this->alsa->Start();
			this->drumModule->Start();
		}
		catch(const std::exception& e)
		{
			return make_error("Could not start module.", error_type_error);
		}
		
		isStarted.store(true);
		return make_error("", error_type_success);
	}

	error eXaDrums::Stop()
	{

		try
		{
			this->alsa->Stop();
			this->drumModule->Stop();
		}
		catch(const std::exception& e)
		{
			return make_error("Could not stop module.", error_type_error);
		}
		
		isStarted.store(false);
		return make_error("", error_type_success);
	}

	error eXaDrums::EnableRecording(bool enable)
	{
		try
		{
			this->drumModule->EnableRecording(enable);
		}
		catch(const std::exception& e)
		{
			return make_error("Could not enable/disable recording.", error_type_warning);
		}

		return make_error("", error_type_success);
	}

	error eXaDrums::RecorderExport_(const char* fileName)
	{
		try
		{
			this->drumModule->RecorderExport(std::string{fileName}); // TODO: throw if expoort fails.
		}
		catch(const std::exception& e)
		{
			return make_error("Could not export track.", error_type_warning);
		}
		
		return make_error("", error_type_success);
	}

	void eXaDrums::GetInstrumentTriggersIds_(int instrumentId, int* data, unsigned int& size) const
	{
		if(data == nullptr)
		{
			size = drumModule->GetInstrumentTriggersIds(instrumentId).size();
			return;
		}

		std::vector<int> trigsIds = drumModule->GetInstrumentTriggersIds(instrumentId);
		std::copy(trigsIds.cbegin(), trigsIds.cend(), data);
		size = trigsIds.size();
	}

	// Metronome

	void eXaDrums::EnableMetronome(bool enable) const
	{
		drumModule->EnableMetronome(enable); // TODO: prevent exceptions.
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

	int eXaDrums::GetTempo() const noexcept
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

		ClickType type = Enums::GetEnumVector<ClickType>()[id];
		metronome->SetClickType(type);

		 return;
	}

	int eXaDrums::GetClickTypeId() const
	{

		ClickType clickType = metronome->GetClickType();
		const std::vector<ClickType>& clickTypes = Enums::GetEnumVector<ClickType>();

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), clickType);
		int index = std::distance(clickTypes.cbegin(), it);

		return index;
	}

	int eXaDrums::GetRhythm() const noexcept
	{
		return this->metronome->GetRhythm();
	}

	void eXaDrums::SetRhythm(int rhythm) noexcept
	{
		this->metronome->SetRhythm(rhythm);
	}

	int eXaDrums::GetBpmeas() const noexcept
	{
		return this->metronome->GetBpmeas();
	}

	void eXaDrums::SetBpmeas(int bpmeas) noexcept
	{
		this->metronome->SetBpmeas(bpmeas);
		return;
	}

	error eXaDrums::SelectKit(int id)
	{
		return ExceptionToError([&] { this->drumModule->SelectKit(id); });
	}

	void eXaDrums::SaveKitConfig(int id) const
	{
		drumModule->SaveKitConfig(id);
		return;
	}

	error eXaDrums::DeleteKit(const int& id)
	{
		if(drumModule->DeleteKit(id))
		{
			return make_error("", error_type_success);
		}
		else
		{
			return make_error("Could not delete kit.", error_type_error);
		}
	}

	void eXaDrums::ReloadKits()
	{

		drumModule->ReloadKits();

		return;
	}

	int eXaDrums::GetNumKits() const noexcept
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

	long long eXaDrums::GetLastTrigTime() const noexcept
	{
		return drumModule->GetLastTrigTime();
	}

	int eXaDrums::GetLastTrigValue() const noexcept
	{
		return drumModule->GetLastTrigValue();
	}

	void eXaDrums::SetTriggerSensorValue(int id, char channel, short data)
	{
		this->drumModule->SetTriggerSensorValue(id, channel, data);
	}

	int eXaDrums::GetSensorsResolution() const noexcept
	{
		return this->drumModule->GetSensorsConfig().resolution;
	}

	bool eXaDrums::IsSensorVirtual() const noexcept
	{
		return this->drumModule->GetSensorsConfig().sensorType == IO::SensorType::Virtual;
	}

	bool eXaDrums::IsSensorSpi() const noexcept
	{
		return this->drumModule->GetSensorsConfig().sensorType == IO::SensorType::Spi;
	}

	std::string eXaDrums::GetAudioDeviceName() const noexcept
	{
		return this->alsa->GetDeviceName();
	}

	// Private Methods

	const char* eXaDrums::GetDataLocation_() const noexcept
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
			size = Enums::GetEnumVector<ClickType>().size();
			return;
		}

		this->clicksTypes.clear();
		{
			std::vector<ClickType> types = Enums::GetEnumVector<ClickType>();
			std::transform(types.cbegin(), types.cend(), std::back_inserter(clicksTypes), [](const ClickType& t) { return Enums::ToString(t); });
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

	long long eXaDrums::GetLastClickTime() const
	{
		return drumModule->GetLastClickTime();
	}


}
