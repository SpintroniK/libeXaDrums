/*
 * KitCreator.cpp
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator.h"

namespace DrumKit
{

	KitCreator::KitCreator()
	{

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

		KitManager::LoadKit(file, this->parameters);
		this->instrument = InstrumentParameters();

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

		Sound::InstrumentSoundType soundType = Util::Enums::InstrumentSoundTypeFromString(typeStr);

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


	// Private Methods


	// Used to test the class
	void KitCreator::Test()
	{

		CreateNewKit();
		SetKitName("Test Kit");

		CreateNewInstrument();
		SetInstrumentName("Test instrument 1");

		// Get an instrument type
		const std::string instrumentType = Util::Enums::InstrumentTypeToString(InstrumentType::Drum);
		SetInstrumentType(instrumentType);

		SetInstrumentVolume(1.0f);

		// Add instrument sounds
		std::string soundLocation;
		std::string instrumentSoundType;
		{
			soundLocation = "SnareDrum/snare1.raw";
			instrumentSoundType = Util::Enums::InstrumentSoundTypeToString(Sound::InstrumentSoundType::Default);
			AddInstrumentSound(soundLocation, instrumentSoundType);

			// And another one
			soundLocation = "SnareDrum/edge1.raw";
			instrumentSoundType = Util::Enums::InstrumentSoundTypeToString(Sound::InstrumentSoundType::RimShot);
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


		return;
	}


} /* namespace DrumKit */
