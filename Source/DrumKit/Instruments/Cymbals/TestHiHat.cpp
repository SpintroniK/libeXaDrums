/*
 * TestHiHat.cpp
 *
 *  Created on: 2 Nov 2016
 *      Author: jeremy
 */

#include "TestHiHat.h"

namespace DrumKit
{

	TestHiHat::TestHiHat(InstrumentParameters parameters, std::shared_ptr<Sound::SoundBank> soundBank) : Instrument(parameters, soundBank),	cymbalSoundId(0)
	{

		return;
	}

	TestHiHat::~TestHiHat()
	{

		return;
	}

	void TestHiHat::SetTriggers(const std::vector<TriggerPtr>& triggers)
	{

		if(parameters.triggersIdsAndLocations.size() != numTriggers)
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

		Sound::InstrumentSoundType soundType = soundInfo.type;
		std::string soundLocation = soundInfo.soundLocation;

		switch (soundType)
		{
			case Sound::InstrumentSoundType::Default:
			{
				cymbalSoundId = soundBank->LoadSound(soundLocation, parameters.volume);
				const Sound::Sound& cymbalSound = soundBank->GetSound(cymbalSoundId);
				const std::vector<short> cymbalSoundData = cymbalSound.GetInternalData();

				for(int i = 0; i < 10; i++)
				{

					Sound::Sound newSound = Sound::SoundProcessor::Muffle(cymbalSoundData, 0.25f/float(i + 1));
					std::vector<short> newSoundData = newSound.GetInternalData();
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
