/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

namespace DrumKit
{

	Drum::Drum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProcessor, std::vector<std::shared_ptr<Trigger>> const& triggers)
	: Instrument(parameters, soundProcessor, triggers)
	{

		this->GenerateSounds();

		return;
	}

	Drum::~Drum()
	{

		return;
	}


	int Drum::GetSoundProps() const
	{

		//TODO Also add the volume to the properties
		return this->soundIds.at(0);
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


