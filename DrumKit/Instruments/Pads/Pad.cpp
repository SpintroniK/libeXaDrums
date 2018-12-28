/*
 * Pad.cpp
 *
 *  Created on: 11 Jun 2017
 *      Author: jeremy
 */

#include "Pad.h"

using namespace Sound;

#include <algorithm>

namespace DrumKit
{

	Pad::Pad(InstrumentParameters parameters, std::shared_ptr<SoundBank> soundBank): Instrument(parameters, soundBank), soundId(0)
	{

		return;
	}

	void Pad::SetTriggers(std::vector<TriggerPtr> const& triggers)
	{

		for(const TriggerPtr& triggerPtr : triggers)
		{

			auto triggerIdAndLocation = std::find_if(parameters.triggersIdsAndLocations.cbegin(), parameters.triggersIdsAndLocations.cend(),
					[triggerPtr](std::pair<int, TriggerLocation> const& idAndLocation) { return (idAndLocation.first == triggerPtr->GetId()); });

			if(triggerIdAndLocation != std::end(parameters.triggersIdsAndLocations))
			{

				TriggerLocation triggerLocation =  triggerIdAndLocation->second;

				switch (triggerLocation)
				{
					case TriggerLocation::DrumHead: this->trigger = triggerPtr; break;

					default: break;
				}
			}
		}



		return;
	}

	void Pad::SetSound(InstrumentSoundInfo const& soundInfo)
	{

		InstrumentSoundType soundType = soundInfo.type;
		std::string soundLocation = soundInfo.soundLocation;

		switch (soundType)
		{
			case InstrumentSoundType::Default: soundId = soundBank->LoadSound(soundLocation, parameters.volume); break;

			default: throw -1; break;
		}


		return;
	}

	void Pad::SetVolume(float volume)
	{

		soundBank->SetSoundVolume(soundId, volume);

		parameters.volume = volume;

		return;
	}

	void Pad::GetSoundProps(int& id, float& volume) const
	{

		TriggerState triggerState = trigger->GetTriggerState();

		if(triggerState.isTrig)
		{
			id = soundId;
			volume = triggerState.value;
		}

		return;
	}

	bool Pad::IsTriggerEvent() const
	{

		TriggerState triggerState = trigger->GetTriggerState();

		return triggerState.isTrig;
	}


} /* namespace DrumKit */
