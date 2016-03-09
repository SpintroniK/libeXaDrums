/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

namespace DrumKit
{

	Drum::Drum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor, std::map<int, std::shared_ptr<Trigger>> const& triggers)
	: Instrument(parameters, soundProcessor, triggers)
	{

		this->GenerateSounds();

		return;
	}

	Drum::~Drum()
	{

		return;
	}


	int Drum::GetSoundProps()
	{

		//TODO Also add the volume to the properties

		for(std::size_t i = 0; i < triggers.size(); i++)
		{


			triggers[i]->Refresh();
			TriggerState triggerState =  triggers[i]->GetTriggerState();

			if(triggerState.isTrig)
			{
				int triggerId = triggerState.sensorId;

				switch (triggerId)
				{
					case 0:
						return soundIds.at(0);
						break;
					default:
						return -1;
						break;
				}
			}

		};



		return -1;
	}

	// PRIVATE

	void Drum::GenerateSounds()
	{

		std::function<void(InstrumentSoundInfo)> genSounds = [this](InstrumentSoundInfo soundInfo)
		{

			std::vector<short> soundData;
			unsigned int soundDuration;

			// Load sound
			Sound::SoundBank::LoadSound(soundInfo.soundLocation, soundData, soundDuration);

			switch (soundInfo.type)
			{
				case Sound::InstrumentSoundType::Default:

						int id;
						soundProcessor->AddSound(id, soundData);

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

}


