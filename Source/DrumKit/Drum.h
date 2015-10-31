/*
 * Drum.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_DRUM_H_
#define SOURCE_DRUMKIT_DRUM_H_

#include "../IO/SensorType.h"
#include "../IO/ISensor.h"
#include "../IO/HddSensor.h"

#include "../Sound/Mixer.h"
#include "Trigger.h"

#include <vector>
#include <string>
#include <memory>

namespace DrumKit
{

	class Drum
	{

	public:

		Drum(int id, int sensorId, IO::SensorType sensorType, std::shared_ptr<Sound::Mixer> const& mixer);
		~Drum();

		void CreateTrigger();
		void Trig();

		void SetDrumName(std::string drumName);
		void SetSoundFile(std::string soundFile);
		void SetCurve(std::vector<float> curve);
		void SetScanTime(unsigned int scanTime);
		void SetThreshold(short threshold);
		void SetMaskTime(int maskTime);


		std::string GetSoundFile() { return this->soundFile; }

	private:

		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<IO::ISensor> sensor;

		int id;
		int sensorId;
		IO::SensorType sensorType;

		std::string drumName;
		std::string soundFile;

		std::vector<float> curve;

		unsigned int scanTime;
		short threshold;
		int maskTime;

		std::shared_ptr<Trigger> trigger;

	};



}


#endif /* SOURCE_DRUMKIT_DRUM_H_ */
