/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

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

		if(parameters.triggersIdsAndLocations.size() != numTriggers)
		{
			throw -1;
		}

		std::for_each(triggers.cbegin(), triggers.cend(), [&](TriggerPtr triggerPtr)
		{

			auto triggerIdAndLocation = std::find_if(parameters.triggersIdsAndLocations.cbegin(),
					parameters.triggersIdsAndLocations.cend(),
					[triggerPtr](std::pair<int, TriggerLocation> const& idAndLocation)
					{
						return (idAndLocation.first == triggerPtr->GetId());
					});

			if(triggerIdAndLocation != std::end(parameters.triggersIdsAndLocations))
			{

				TriggerLocation triggerLocation =  (*triggerIdAndLocation).second;

				switch (triggerLocation)
				{
					case TriggerLocation::DrumHead:
					{
						this->drumHeadTrigger = triggerPtr;
					}
						break;

					case TriggerLocation::Rim:
					{
						this->drumRimTrigger = triggerPtr;
					}
						break;

					default:
						break;
				}

			}


		});


		return;
	}

	void Drum::SetSound(InstrumentSoundInfo const& soundInfo,
						Sound::SoundBank const& soundBank,
						std::shared_ptr<Sound::SoundProcessor> const& soundProcessor)
	{

		Sound::InstrumentSoundType soundType = soundInfo.type;
		std::string soundLocation = soundInfo.soundLocation;

		switch (soundType)
		{
			case Sound::InstrumentSoundType::RimShot:
			{

				// Use SoundBank to load sound
				Sound::Sound sound = soundBank.LoadSound(soundLocation, 0);

				// Use that sound for the rim shot
				drumRimSound = std::make_shared<Sound::Sound>(sound);

			}
				break;

			case Sound::InstrumentSoundType::Default:
			{

				// Use SoundBank to load sound
				Sound::Sound sound = soundBank.LoadSound(soundLocation, 1);

				// Use that sound for the drum head
				drumHeadSound = std::make_shared<Sound::Sound>(sound);

			}
				break;

			default:
				throw -1;
				break;
		}


		return;
	}

	bool Drum::isTriggerEvent()
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


