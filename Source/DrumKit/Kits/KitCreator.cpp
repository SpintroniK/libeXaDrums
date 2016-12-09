/*
 * KitCreator.cpp
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator.h"

#include "../../Sound/SoundBank/SoundBank.h"

#include "../Instruments/Cymbals/TestHiHat.h"
#include "../Instruments/Drums/TestDrum.h"


using namespace Sound;

namespace DrumKit
{

	KitCreator::KitCreator(const std::string& dataLoc)
	{

		kitsDirectory = std::string(dataLoc) + "Kits/";

		soundFiles = SoundBank::GetSoundNames(dataLoc);

		return;
	}

	KitCreator::~KitCreator()
	{

		return;
	}

	void KitCreator::CreateNewKit()
	{

		this->parameters = KitParameters();
		this->instrument = InstrumentParameters();

		return;
	}

	void KitCreator::CreateFromModel(const std::string& file)
	{

		KitManager::LoadKit(this->kitsDirectory + file, this->parameters);
		this->instrument = InstrumentParameters();

		return;
	}

	void KitCreator::SaveKit(const std::string& file) const
	{

		KitManager::SaveKit(this->kitsDirectory + file, this->parameters);

		return;
	}

	void KitCreator::AddInstrumentToKit()
	{

		this->parameters.instrumentParameters.push_back(this->instrument);
		this->instrument = InstrumentParameters();

		return;
	}

	void KitCreator::CreateNewInstrument()
	{

		this->instrument = InstrumentParameters();
		this->instrument.id = (int) this->parameters.instrumentParameters.size();

		return;
	}

	void KitCreator::SetInstrumentType(const std::string& typeStr)
	{

		InstrumentType type =  Util::Enums::InstrumentTypeFromString(typeStr);
		this->instrument.instrumentType = type;

		return;
	}

	void KitCreator::AddInstrumentSound(const std::string& file, const std::string& typeStr)
	{

		InstrumentSoundType soundType = Util::Enums::InstrumentSoundTypeFromString(typeStr);

		InstrumentSoundInfo instrumentSoundInfo;
		{
			instrumentSoundInfo.id = (int) this->instrument.soundsInfo.size();
			instrumentSoundInfo.soundLocation = file;
			instrumentSoundInfo.type = soundType;
		}

		this->instrument.soundsInfo.push_back(instrumentSoundInfo);

		return;
	}

	void KitCreator::AddInstrumentTrigger(const int id, const std::string& location)
	{


		TriggerLocation trigLoc = Util::Enums::TriggerLocationFromString(location);

		this->instrument.triggersIdsAndLocations.push_back(std::pair<int, TriggerLocation>{id, trigLoc});

		return;
	}


	int KitCreator::GetNumSounds(const std::string& instrumentType) const
	{

		InstrumentType type = Util::Enums::InstrumentTypeFromString(instrumentType);

		switch (type)
		{
			case InstrumentType::TestDrum: return (int)TestDrum::soundsTypes.size(); break;
			case InstrumentType::HiHat: return (int)TestHiHat::soundsTypes.size(); break;

			default: throw -1; break;
		}

	}


	std::string KitCreator::GetSoundTypeById(const std::string& instrumentType, int id) const
	{

		InstrumentType type = Util::Enums::InstrumentTypeFromString(instrumentType);

		InstrumentSoundType soundType;

		switch(type)
		{
			case InstrumentType::TestDrum: soundType = TestDrum::soundsTypes[id]; break;
			case InstrumentType::HiHat: soundType = TestHiHat::soundsTypes[id]; break;

			default: throw -1; break;
		}

		return Util::Enums::InstrumentSoundTypeToString(soundType);
	}

	std::string KitCreator::GetTriggerTypeById(const std::string& instrumentType, int id) const
	{

		InstrumentType type = Util::Enums::InstrumentTypeFromString(instrumentType);

		TriggerLocation triggerType;

		switch(type)
		{
			case InstrumentType::TestDrum: triggerType = TestDrum::triggersLocations[id]; break;
			case InstrumentType::HiHat: triggerType = TestHiHat::triggersLocations[id]; break;

			default: throw -1; break;
		}

		return Util::Enums::TriggerLocationToString(triggerType);
	}

	int KitCreator::GetNumTriggers(const std::string& instrumentType) const
	{

		InstrumentType type = Util::Enums::InstrumentTypeFromString(instrumentType);

		switch (type)
		{
			case InstrumentType::TestDrum: return (int)TestDrum::triggersLocations.size(); break;
			case InstrumentType::HiHat: return (int)TestHiHat::triggersLocations.size(); break;

			default: throw -1; break;
		}

	}


	std::string KitCreator::GetInstrumentTypeById(int id) const
	{

		InstrumentType type = Util::Enums::GetInstrumentTypes()[id];
		std::string typeStr = Util::Enums::InstrumentTypeToString(type);

		return typeStr;
	}



	// Private Methods


	// Used to test the class
	void KitCreator::Test()
	{

		CreateNewKit();
		SetKitName("Test Kit");

		CreateNewInstrument();
		SetInstrumentName("Test instrument 1");

		// Get an instrument type
		const std::string instrumentType = Util::Enums::InstrumentTypeToString(InstrumentType::TestDrum);
		SetInstrumentType(instrumentType);

		SetInstrumentVolume(1.0f);

		// Add instrument sounds
		std::string soundLocation;
		std::string instrumentSoundType;
		{
			soundLocation = "SnareDrum/snare1.raw";
			instrumentSoundType = Util::Enums::InstrumentSoundTypeToString(InstrumentSoundType::Default);
			AddInstrumentSound(soundLocation, instrumentSoundType);

			// And another one
			soundLocation = "SnareDrum/edge1.raw";
			instrumentSoundType = Util::Enums::InstrumentSoundTypeToString(InstrumentSoundType::RimShot);
			AddInstrumentSound(soundLocation, instrumentSoundType);
		}

		// Add triggers
		int id;
		std::string triggerLocation;
		{
			id = 0;
			triggerLocation = Util::Enums::TriggerLocationToString(TriggerLocation::DrumHead);
			AddInstrumentTrigger(id, triggerLocation);

			id = 1;
			triggerLocation = Util::Enums::TriggerLocationToString(TriggerLocation::Rim);
			AddInstrumentTrigger(id, triggerLocation);
		}

		AddInstrumentToKit();

		this->SaveKit("testKit_.xml");


		return;
	}


} /* namespace DrumKit */
