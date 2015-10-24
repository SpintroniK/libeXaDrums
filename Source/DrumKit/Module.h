/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_

#include "Kit.h"
#include "Curve.h"
#include "Curves.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>

#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>


namespace DrumKit
{

	class Module
	{

	public:

		Module();
		Module(std::string dir);
		virtual ~Module();

		void LoadKit(std::string fileLoc, Kit& kit);

		void Start();
		void Stop();

		const std::vector<SoundParams>& soundParameters;

		void GetDirectory(std::string& dir) const;

	private:

		void Run();

		bool GetDrumParams(xmlNode* drumName, std::vector<Drum>& drum);
		void GetDrumCurve(std::string curveName, std::vector<float>& curve);
		DrumCurve GetCurveType(std::string curveName);
		void AddSound(std::string fileLocation, size_t soundId);

		std::string directory;
		std::vector<SoundParams> sndParams;
		std::thread playThread;
		std::atomic<bool> isPlay;


	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_MODULE_H_ */
