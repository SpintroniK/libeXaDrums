/*
 * TestHiHat.cpp
 *
 *  Created on: 2 Nov 2016
 *      Author: jeremy
 */

#include "TestHiHat.h"

#include "../../../Sound/InstrumentSoundType.h"
#include "../../../Sound/SoundProcessor/SoundProcessor.h"

#include <algorithm>


using namespace Sound;

namespace DrumKit
{


	const std::vector<TriggerLocation> TestHiHat::triggersLocations{TriggerLocation::DrumHead, TriggerLocation::Rim};
	const std::vector<InstrumentSoundType> TestHiHat::soundsTypes{InstrumentSoundType::Default};

	TestHiHat::TestHiHat(InstrumentParameters parameters, std::shared_ptr<SoundBank> soundBank) : Instrument(parameters, soundBank), cymbalSoundId(0)
	{

		return;
	}

	TestHiHat::~TestHiHat()
	{

		return;
	}

	void TestHiHat::SetTriggers(const std::vector<TriggerPtr>& triggers)
	{

		if(parameters.triggersIdsAndLocations.size() != triggersLocations.size())
		{
			throw -1;
		}

		for(const TriggerPtr& triggerPtr : triggers)
		{

			auto triggerIdAndLocation = std::find_if(parameters.triggersIdsAndLocations.cbegin(), parameters.triggersIdsAndLocations.cend(),
					[triggerPtr](std::pair<int, TriggerLocation> const& idAndLocation) { return (idAndLocation.first == triggerPtr->GetId()); });


			if(triggerIdAndLocation != std::end(parameters.triggersIdsAndLocations))
			{

				TriggerLocation triggerLocation =  triggerIdAndLocation->second;

				switch (triggerLocation)
				{
					case TriggerLocation::DrumHead: this->cymbalTrigger = triggerPtr; break;
					case TriggerLocation::Rim: this->pedalTrigger = triggerPtr; break;

					default: break;
				}
			}
		}

		return;
	}

	void TestHiHat::SetSound(const InstrumentSoundInfo& soundInfo)
	{

		InstrumentSoundType soundType = soundInfo.type;
		std::string soundLocation = soundInfo.soundLocation;


		switch (soundType)
		{
			case InstrumentSoundType::Default:
			{
				cymbalSoundId = soundBank->LoadSound(soundLocation, parameters.volume);
				const Sound::Sound& cymbalSound = soundBank->GetSound(cymbalSoundId);
				const std::vector<short>& cymbalSoundData = cymbalSound.GetInternalData();

				for(int i = 0; i < 10; i++)
				{

					const Sound::Sound& newSound = SoundProcessor::Muffle(cymbalSoundData, 0.25f/float(i + 1));
					const std::vector<short>& newSoundData = newSound.GetInternalData();
					int newSoundId = soundBank->AddSound(newSoundData, parameters.volume);

					hiHatSoundsIds.push_back(newSoundId);
				}

				break;
			}

			default: throw -1; break;
		}

		return;
	}

	void TestHiHat::SetVolume(float volume)
	{

		soundBank->SetSoundVolume(cymbalSoundId, volume);

		std::for_each(hiHatSoundsIds.cbegin(), hiHatSoundsIds.cend(), [&](const int& id) { soundBank->SetSoundVolume(id, volume); });

		parameters.volume = volume;

		return;
	}


	bool TestHiHat::IsTriggerEvent() const
	{

		TriggerState cymbalTriggerState = cymbalTrigger->GetTriggerState();

		if(cymbalTriggerState.isTrig)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	void TestHiHat::GetSoundProps(int& id, float& volume) const
	{

		TriggerState cymbalTriggerState = cymbalTrigger->GetTriggerState();
		TriggerState pedalTriggerState = pedalTrigger->GetTriggerState();


		if(cymbalTriggerState.isTrig)
		{

			float pedalPosition = pedalTriggerState.value;
			int hiHatSoundIndex = cymbalSoundId + std::floor(pedalPosition * 10) + 1;


			id = hiHatSoundIndex;
			volume = cymbalTriggerState.value;
		}

		return;
	}


} /* namespace DrumKit */
