/*
 * KitCreator.cpp
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator.h"

#include "../../Sound/SoundBank/SoundBank.h"

#include "../Triggers/TriggerManager.h"
#include "../Instruments/Cymbals/TestHiHat.h"
#include "../Instruments/Drums/TestDrum.h"

#include <algorithm>

using namespace Sound;
using namespace Util;

namespace DrumKit
{

	KitCreator::KitCreator(const std::string& dataLoc)
	{

		kitsDirectory = std::string(dataLoc) + "Kits/";

		// Sound Files
		soundFiles = SoundBank::GetSoundFiles(dataLoc);

		// Triggers
		std::vector<TriggerParameters> trigsParams;
		TriggerManager::LoadTriggersConfig(dataLoc, trigsParams);
		std::transform(trigsParams.cbegin(), trigsParams.cend(), std::back_inserter(triggersIds), [&](const TriggerParameters& p) { return p.sensorId; });

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

	void KitCreator::SaveKit() const
	{

		std::string file = this->parameters.kitName + ".xml";
		SaveKit(file);

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

		InstrumentType type =  Enums<InstrumentType>::ToElement(typeStr);
		this->instrument.instrumentType = type;

		return;
	}

	void KitCreator::AddInstrumentSound(const std::string& file, const std::string& typeStr)
	{

		InstrumentSoundType soundType = Enums<InstrumentSoundType>::ToElement(typeStr);

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


		TriggerLocation trigLoc = Enums<TriggerLocation>::ToElement(location);

		this->instrument.triggersIdsAndLocations.push_back(std::pair<int, TriggerLocation>{id, trigLoc});

		return;
	}


	std::vector<std::string> KitCreator::GetSoundTypes(const std::string& instrumentType) const
	{

		InstrumentType type = Enums<InstrumentType>::ToElement(instrumentType);

		std::vector<InstrumentSoundType> sndTypes;

		switch(type)
		{
			case InstrumentType::TestDrum: sndTypes = TestDrum::soundsTypes; break;
			case InstrumentType::HiHat: sndTypes = TestHiHat::soundsTypes; break;

			default: throw -1; break;
		}

		std::vector<std::string> soundsTypes;
		std::transform(sndTypes.cbegin(), sndTypes.cend(), std::back_inserter(soundsTypes), [](const InstrumentSoundType& t) { return Enums<InstrumentSoundType>::ToString(t); });

		return soundsTypes;
	}


	std::vector<std::string> KitCreator::GetTriggersLocations(const std::string& instrumentType) const
	{

		InstrumentType type = Enums<InstrumentType>::ToElement(instrumentType);

		std::vector<TriggerLocation> trigsLocs;

		switch(type)
		{
			case InstrumentType::TestDrum: trigsLocs = TestDrum::triggersLocations; break;
			case InstrumentType::HiHat: trigsLocs = TestHiHat::triggersLocations; break;

			default: throw -1; break;
		}

		std::vector<std::string> triggersLocations;
		std::transform(trigsLocs.cbegin(), trigsLocs.cend(), std::back_inserter(triggersLocations), [](const TriggerLocation& l) { return Enums<TriggerLocation>::ToString(l); });

		return triggersLocations;
	}



	std::vector<std::string> KitCreator::GetInstrumentsTypes() const
	{

		std::vector<InstrumentType> types = Enums<InstrumentType>::GetEnumVector();

		std::vector<std::string> instrumentTypes;
		std::transform(types.cbegin(), types.cend(), std::back_inserter(instrumentTypes), [](const InstrumentType& t) { return Enums<InstrumentType>::ToString(t); });

		return instrumentTypes;
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
		const std::string instrumentType = Enums<InstrumentType>::ToString(InstrumentType::TestDrum);
		SetInstrumentType(instrumentType);

		SetInstrumentVolume(1.0f);

		// Add instrument sounds
		std::string soundLocation;
		std::string instrumentSoundType;
		{
			soundLocation = "SnareDrum/snare1.raw";
			instrumentSoundType = Enums<InstrumentSoundType>::ToString(InstrumentSoundType::Default);
			AddInstrumentSound(soundLocation, instrumentSoundType);

			// And another one
			soundLocation = "SnareDrum/edge1.raw";
			instrumentSoundType = Enums<InstrumentSoundType>::ToString(InstrumentSoundType::RimShot);
			AddInstrumentSound(soundLocation, instrumentSoundType);
		}

		// Add triggers
		int id;
		std::string triggerLocation;
		{
			id = 0;
			triggerLocation = Enums<TriggerLocation>::ToString(TriggerLocation::DrumHead);
			AddInstrumentTrigger(id, triggerLocation);

			id = 1;
			triggerLocation = Enums<TriggerLocation>::ToString(TriggerLocation::Rim);
			AddInstrumentTrigger(id, triggerLocation);
		}

		AddInstrumentToKit();

		this->SaveKit("testKit_.xml");


		return;
	}


} /* namespace DrumKit */
