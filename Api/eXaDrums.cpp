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

	eXaDrums::eXaDrums(const char* dataLoc) noexcept : isStarted(false)
	{

		this->init_error = ExceptionToError([&]
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
		});

		return;
	}

	eXaDrums::~eXaDrums()
	{

	}

	// Module

	error eXaDrums::Start_()
	{

		try
		{
			this->alsa->Start();
			this->drumModule->Start();
		}
		catch(const Exception&)
		{
			return ExceptionToError([&] { throw; });
		}
		catch(...)
		{
			return make_error("Could not start module.", error_type_error);
		}
		
		isStarted.store(true);
		return make_error("", error_type_success);
	}

	error eXaDrums::Stop_()
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

	error eXaDrums::EnableRecording_(bool enable)
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
			this->drumModule->RecorderExport(std::string{fileName});
		}
		catch(const std::exception& e)
		{
			return make_error("Could not export track.", error_type_warning);
		}
		
		return make_error("", error_type_success);
	}

	error eXaDrums::RecorderExportPCM_(const char* fileName)
	{
		try
		{
			this->drumModule->RecorderExportPCM(std::string{fileName});
		}
		catch(const std::exception& e)
		{
			return make_error("Could not export track.", error_type_warning);
		}
		
		return make_error("", error_type_success);
	}

	error eXaDrums::RecorderPurgeTempFile_()
	{
		try
		{
			this->drumModule->RecorderPurgeTempFile();
		}
		catch(const std::exception& e)
		{
			return make_error("Unknown error.", error_type_warning);
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

	error eXaDrums::GetTriggerValue_(size_t id, float& value)
	{
		try
		{
			value = drumModule->GetTriggerValue(id);
		}
		catch(const Exception& e)
		{
			return make_error(e.what(), e.type());
		}

		return make_error("", error_type_success);
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

	void eXaDrums::ChangeTempo(std::size_t tempo) const
	{
		drumModule->ChangeTempo(tempo);
		return;
	}

	void eXaDrums::ChangeClickVolume(std::size_t volume) const
	{
		drumModule->ChangeClickVolume(volume);
		return;
	}

	std::size_t eXaDrums::GetTempo() const noexcept
	{
		return metronome->GetTempo();
	}

	std::size_t eXaDrums::GetClickVolume() const noexcept
	{
		return std::size_t(drumModule->GetClickVolume() * 100.0f);
	}

	void eXaDrums::SaveMetronomeConfig() const
	{
		metronome->SaveConfig(dataLocation + metronomeConfigFile, metronome->GetParameters());
		return;
	}


	void eXaDrums::SetClickType(std::size_t id)
	{
		const auto types = Enums::GetEnumVector<ClickType>();

		if(id >= types.size())
		{
			ClickType type = types.back();
			metronome->SetClickType(type);
		}
		else
		{
			ClickType type = types[id];
			metronome->SetClickType(type);
		}

		 return;
	}

	std::size_t eXaDrums::GetClickTypeId() const
	{

		ClickType clickType = metronome->GetClickType();
		const std::vector<ClickType>& clickTypes = Enums::GetEnumVector<ClickType>();

		auto it = std::find(clickTypes.cbegin(), clickTypes.cend(), clickType);
		std::size_t index = std::distance(clickTypes.cbegin(), it);

		return index;
	}

	std::size_t eXaDrums::GetRhythm() const noexcept
	{
		return this->metronome->GetRhythm();
	}

	void eXaDrums::SetRhythm(std::size_t rhythm) noexcept
	{
		this->metronome->SetRhythm(rhythm);
	}

	std::size_t eXaDrums::GetBpmeas() const noexcept
	{
		return this->metronome->GetBpmeas();
	}

	void eXaDrums::SetBpmeas(std::size_t bpmeas) noexcept
	{
		this->metronome->SetBpmeas(bpmeas);
		return;
	}

	error eXaDrums::SelectKit_(int id)
	{
		return ExceptionToError([&] { this->drumModule->SelectKit(id); });
	}

	error eXaDrums::SaveKitConfig_(std::size_t id) const
	{
		return ExceptionToError([&] { drumModule->SaveKitConfig(id); });
	}

	error eXaDrums::DeleteKit_(int id)
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

	std::size_t eXaDrums::GetNumKits() const noexcept
	{
		return drumModule->GetNumKits();
	}

	error eXaDrums::SetInstrumentVolume_(std::size_t id, std::size_t volume)
	{

		float vol = float(volume) / 100.0f;

		return ExceptionToError([&] { drumModule->SetInstrumentVolume(id, vol); });
	}

	std::size_t eXaDrums::GetInstrumentVolume(std::size_t id) const
	{

		auto volume = (std::size_t) std::floor( 100.0f * drumModule->GetInstrumentVolume(id));

		return volume;
	}

	long long eXaDrums::GetLastTrigTime() const noexcept
	{
		return drumModule->GetLastTrigTime();
	}

	std::size_t eXaDrums::GetLastTrigValue() const noexcept
	{
		return drumModule->GetLastTrigValue();
	}

	/**
	 * @brief Set external trigger's data (error handling's responsability is left to the user)
	 * 
	 * @param id trigger id
	 * @param channel 
	 * @param data trigger's output value
	 */
	void eXaDrums::SetTriggerSensorValue(std::size_t id, char channel, short data)
	{
		this->drumModule->SetTriggerSensorValue(id, channel, data);
	}

	std::size_t eXaDrums::GetSensorsResolution() const noexcept
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

	const char* eXaDrums::GetVersion_() noexcept
	{
		return LIBEXADRUMS_VERSION;
	}

	const char* eXaDrums::GetKitDataFileName_()
	{

		try
		{		
			std::string kitLocation = this->drumModule->GetKitLocation();
			std::size_t pos = kitLocation.find_last_of("/");

			this->kitDataFileName = kitLocation.substr(pos + 1, std::string::npos);
		}
		catch(...)
		{
			return nullptr;
		}


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

	double eXaDrums::GetClickPosition() const noexcept
	{
		return drumModule->GetClickPosition();
	}

	long long eXaDrums::GetLastClickTime() const noexcept
	{
		return drumModule->GetLastClickTime();
	}


}
