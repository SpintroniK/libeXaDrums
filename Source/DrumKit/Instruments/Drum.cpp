/*
 * Drum.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#include "Drum.h"

namespace DrumKit
{

	Drum::Drum(InstrumentParameters parameters, std::shared_ptr<Sound::SoundProcessor> soundProc)
	: Instrument(parameters, soundProc)
	{

		this->GenerateSounds();

		return;
	}

	Drum::~Drum()
	{

		return;
	}

	bool Drum::Trig(float& strength)
	{

		short value = this->sensor->GetData(parameters.sensorId);

		bool isTrig = this->trigger->Trig(value, strength);

		return isTrig;
	}

	int Drum::GetSoundProps() const
	{
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


