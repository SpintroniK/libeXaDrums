/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

#include <iostream>

namespace DrumKit
{

	Drum::Drum(InstrumentParameters parameters)
	: Instrument(parameters),
	  drumHeadTrigger(nullptr),
	  drumRimTrigger(nullptr)
	{


		return;
	}

	Drum::~Drum()
	{

		return;
	}


	void Drum::SetTriggers(std::vector<TriggerPtr> triggers)
	{

		std::for_each(triggers.cbegin(), triggers.cend(), [this](TriggerPtr triggerPtr)
		{

			auto triggerIdAndLocation = std::find_if(parameters.triggersIdsAndLocations.cbegin(),
					parameters.triggersIdsAndLocations.cend(),
					[triggerPtr](std::tuple<int, TriggerLocation> idAndLocation)
					{
						return (std::get<0>(idAndLocation) == triggerPtr->GetId());
					});

			if(triggerIdAndLocation != std::end(parameters.triggersIdsAndLocations))
			{

				TriggerLocation triggerLocation =  std::get<1>(*triggerIdAndLocation);

				switch (triggerLocation)
				{
					case TriggerLocation::DrumHead:
					{
						this->drumHeadTrigger = triggerPtr;
						TriggerState headTriggerState = drumHeadTrigger->GetTriggerState();
						std::cout << "Head: " << headTriggerState.sensorId << std::endl;
					}
						break;

					case TriggerLocation::Rim:
					{
						this->drumRimTrigger = triggerPtr;
						TriggerState rimTriggerState = drumRimTrigger->GetTriggerState();
						std::cout << "Rim: " << rimTriggerState.sensorId << std::endl;
					}
						break;

					default:
						break;
				}

			}


		});


		return;
	}

	void Drum::SetSound(Sound::SoundPtr const soundPtr, Sound::SoundProcessor const soundProcessor)
	{




		return;
	}

	bool Drum::isTriggerEvent() const
	{

		TriggerState headTriggerState = drumHeadTrigger->GetTriggerState();
		TriggerState rimTriggerState = drumRimTrigger->GetTriggerState();

		if(headTriggerState.isTrig || rimTriggerState.isTrig)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	Sound::SoundPtr Drum::GetSound()
	{

		return drumHeadSound;
	}

	// PRIVATE

	/*void Drum::GenerateSounds()
	{

		std::function<void(InstrumentSoundInfo)> genSounds = [this](InstrumentSoundInfo soundInfo)
		{

			std::vector<short> soundData;
			unsigned int soundDuration;

			// Load sound
			//Sound::SoundBank::LoadSound(soundInfo.soundLocation, soundData, soundDuration);

			switch (soundInfo.type)
			{
				case Sound::InstrumentSoundType::Default:

						int id;
						//soundProcessor->AddSound(id, soundData);

						// Internal Id = 0 for default sound
						soundIds.insert(std::pair<int, int>(0, id));

					break;
				default:
					break;
			}




		};


		std::for_each(parameters.soundsInfo.cbegin(), parameters.soundsInfo.cend(), genSounds);

		return;
	}
	*/
}


