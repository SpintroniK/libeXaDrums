/*
 * KitCreator.cpp
 *
 *  Created on: 9 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator.h"

#include "../../Sound/SoundBank/SoundBank.h"
#include "../Instruments/InstrumentFactory.h"

#include <algorithm>

using namespace Sound;
using namespace Util;

namespace DrumKit
{

	KitCreator::KitCreator(const std::string& dataLoc) noexcept
	: dataFolder{dataLoc}, kitsDirectory(dataLoc + "Kits/"), instrument() //, soundFiles(SoundBank::GetSoundFiles(dataLoc))
	{



		return;
	}

	KitCreator::~KitCreator()
	{

		return;
	}

	void KitCreator::CreateNewKit() noexcept
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

	void KitCreator::SaveKit(const std::string& file, bool fullPath) const
	{

		if(fullPath)
		{
			KitManager::SaveKit(file, this->parameters);
		}
		else
		{
			KitManager::SaveKit(this->kitsDirectory + file, this->parameters);
		}


		return;
	}

	void KitCreator::SaveKit() const
	{

		std::string configFilePath = this->parameters.configFilePath;

		if(configFilePath.empty())
		{
			std::string file = this->parameters.kitName + ".xml";
			SaveKit(file);
		}
		else
		{
			SaveKit(configFilePath, true);
		}

		return;
	}

	void KitCreator::AddInstrumentToKit() noexcept
	{

		this->parameters.instrumentParameters.push_back(this->instrument);
		this->instrument = InstrumentParameters();

		return;
	}

	void KitCreator::CreateNewInstrument() noexcept
	{

		this->instrument = InstrumentParameters();
		this->instrument.id = (int) this->parameters.instrumentParameters.size();

		return;
	}

	void KitCreator::RemoveInstrument(std::size_t i) noexcept
	{

		if(parameters.instrumentParameters.size() > 1)
		{
			parameters.instrumentParameters.erase(parameters.instrumentParameters.begin() + i);
		}

		return;
	}

	void KitCreator::RemoveLastInstrument() noexcept
	{
		if(parameters.instrumentParameters.size() > 1)
		{
			parameters.instrumentParameters.erase(parameters.instrumentParameters.end() - 1);
		}

		return;
	}

	void KitCreator::SetInstrumentType(const std::string& typeStr)
	{

		InstrumentType type =  Enums::ToElement<InstrumentType>(typeStr);
		this->instrument.instrumentType = type;

		return;
	}

	void KitCreator::AddInstrumentSound(const std::string& file, const std::string& typeStr)
	{

		InstrumentSoundType soundType = Enums::ToElement<InstrumentSoundType>(typeStr);

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


		TriggerLocation trigLoc = Enums::ToElement<TriggerLocation>(location);

		this->instrument.triggersIdsAndLocations.push_back(std::pair<int, TriggerLocation>{id, trigLoc});

		return;
	}


	void KitCreator::SetInstrumentTriggersIdsAndLocs(int id, const std::vector<std::pair<int, std::string>>& trigsIdsAndLocs)
	{

		InstrumentParameters& instrument = parameters.instrumentParameters[id];
		instrument.triggersIdsAndLocations.clear();
		instrument.triggersIdsAndLocations.resize(trigsIdsAndLocs.size());

		for(std::size_t i = 0; i < trigsIdsAndLocs.size(); i++)
		{
			instrument.triggersIdsAndLocations[i].first = trigsIdsAndLocs[i].first;

			TriggerLocation trigLoc = Enums::ToElement<TriggerLocation>(trigsIdsAndLocs[i].second);
			instrument.triggersIdsAndLocations[i].second = trigLoc;
		}

		return;
	}

	void KitCreator::SetInstrumentSoundsTypesAndLocs(int id, const std::vector<std::pair<std::string, std::string>>& sndsTypesAndLocs)
	{

		InstrumentParameters& instrument = parameters.instrumentParameters[id];
		instrument.soundsInfo.clear();
		instrument.soundsInfo.resize(sndsTypesAndLocs.size());

		for(std::size_t i = 0; i < sndsTypesAndLocs.size(); i++)
		{

			instrument.soundsInfo[i].type  = Enums::ToElement<InstrumentSoundType>(sndsTypesAndLocs[i].first);
			instrument.soundsInfo[i].soundLocation = sndsTypesAndLocs[i].second;

		}

		return;
	}

	std::string KitCreator::GetInstrumentType(int i) const
	{

		InstrumentType type = parameters.instrumentParameters[i].instrumentType;
		std::string typeStr = Enums::ToString(type);

		return typeStr;
	}

	std::vector<int> KitCreator::GetInstrumentsTriggersIds(int i) const
	{

		const auto& triggers = parameters.instrumentParameters[i].triggersIdsAndLocations;

		std::vector<int> triggersIds(triggers.size());
		std::transform(triggers.cbegin(), triggers.cend(), triggersIds.begin(), [](const std::pair<int, TriggerLocation>& t){ return t.first; });

		return triggersIds;
	}

	std::vector<std::string> KitCreator::GetInstrumentTriggersLocations(int i) const
	{

		const auto& trigs = parameters.instrumentParameters[i].triggersIdsAndLocations;

		std::vector<std::string> triggersLocations(trigs.size());
		std::transform(trigs.cbegin(), trigs.cend(), triggersLocations.begin(), [](const std::pair<int, TriggerLocation>& t){ return Enums::ToString(t.second); });

		return triggersLocations;
	}

	std::vector<std::string> KitCreator::GetInstrumentSoundsTypes(int i) const
	{

		const auto& sounds = parameters.instrumentParameters[i].soundsInfo;

		std::vector<std::string> soundsTypes(sounds.size());
		std::transform(sounds.cbegin(), sounds.cend(), soundsTypes.begin(), [](const InstrumentSoundInfo& s) { return Enums::ToString(s.type); });

		return soundsTypes;
	}

	std::vector<std::string> KitCreator::GetInstrumentSoundsLocs(int i) const
	{

		const auto& sounds = parameters.instrumentParameters[i].soundsInfo;

		std::vector<std::string> soundsLocs(sounds.size());
		std::transform(sounds.cbegin(), sounds.cend(), soundsLocs.begin(), [](const InstrumentSoundInfo& s) { return s.soundLocation; });

		return soundsLocs;
	}


	std::vector<std::string> KitCreator::GetSoundTypes(const std::string& instrumentType) const
	{

		InstrumentType type = Enums::ToElement<InstrumentType>(instrumentType);

		std::vector<InstrumentSoundType> sndTypes = InstrumentFactory::GetSoundsTypes(type);

		std::vector<std::string> soundsTypes;
		std::transform(sndTypes.cbegin(), sndTypes.cend(), std::back_inserter(soundsTypes), [](const InstrumentSoundType& t) { return Enums::ToString(t); });

		return soundsTypes;
	}


	std::vector<std::string> KitCreator::GetTriggersLocations(const std::string& instrumentType) const
	{

		InstrumentType type = Enums::ToElement<InstrumentType>(instrumentType);

		std::vector<TriggerLocation> trigsLocs = InstrumentFactory::GetTriggersTypes(type);

		std::vector<std::string> triggersLocations;
		std::transform(trigsLocs.cbegin(), trigsLocs.cend(), std::back_inserter(triggersLocations), [](const TriggerLocation& l) { return Enums::ToString(l); });

		return triggersLocations;
	}



	std::vector<std::string> KitCreator::GetInstrumentsTypes() const
	{

		std::vector<InstrumentType> types = Enums::GetEnumVector<InstrumentType>();

		std::vector<std::string> instrumentTypes;
		std::transform(types.cbegin(), types.cend(), std::back_inserter(instrumentTypes), [](const InstrumentType& t) { return Enums::ToString(t); });

		return instrumentTypes;
	}

	std::vector<std::string> KitCreator::GetInstrumentsNames() const
	{

		const std::vector<InstrumentParameters>& instruments = this->parameters.instrumentParameters;

		std::vector<std::string> instrumentsNames;
		std::transform(instruments.cbegin(), instruments.cend(), std::back_inserter(instrumentsNames),[](const InstrumentParameters& i) { return i.instrumentName; });

		return instrumentsNames;
	}


} /* namespace DrumKit */
