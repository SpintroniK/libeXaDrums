/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_


#include "../../Sound/SoundProcessor/SoundProcessor.h"
#include "../../Sound/SoundProcessor/Curves/CurveType.h"
#include "../../Sound/SoundProcessor/Curves/Curves.h"
#include "../../Sound/SoundBank/SoundBank.h"
#include "../../IO/SensorType.h"

#include "../Instruments/InstrumentParameters.h"
#include "../KitManager/KitParameters.h"
#include "../Instruments/Instrument.h"
#include "../Instruments/Drum.h"


#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <algorithm>
#include <functional>



namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::SoundProcessor> const& soundProc);
		virtual ~Module();

		void LoadKit(std::string fileLoc);

		void Start();
		void Stop();

		void GetDirectory(std::string& dir) const;

	private:

		void Run();

		KitParams kitParameters;

		IO::SensorType sensorType;

		std::string directory;
		std::vector<std::shared_ptr<Instrument>> instruments;

		std::thread playThread;
		std::atomic<bool> isPlay;
		std::shared_ptr<Sound::SoundProcessor> soundProc;


	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
