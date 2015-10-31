/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_

#include "../../IO/SensorType.h"
#include "../../Sound/Mixer.h"

#include "../Drum.h"
#include "../Kit.h"
#include "../Curves/Curves.h"
#include "../Curves/Curve.h"
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>



namespace DrumKit
{

	class Module
	{

	public:

		Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::Mixer> const& mixer);
		virtual ~Module();

		void LoadKit(std::string fileLoc, Kit& kit);

		void Start();
		void Stop();

		std::vector<SoundParams> soundParameters;

		void GetDirectory(std::string& dir) const;

	private:

		void Run();

		bool GetDrumParams(xmlNode* drumName, std::vector<Drum>& drum);
		void GetDrumCurve(std::string curveName, std::vector<float>& curve);
		DrumCurve GetCurveType(std::string curveName);
		void AddSound(std::string fileLocation, size_t soundId);

		IO::SensorType sensorType;

		std::string directory;
		std::vector<SoundParams> sndParams;
		std::vector<Drum> drums;

		std::thread playThread;
		std::atomic<bool> isPlay;
		std::shared_ptr<Sound::Mixer> mixer;


	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
