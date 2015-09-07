/*
 * Kit.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef RASPIDRUMS_SOURCE_DRUMKIT_KIT_H_
#define RASPIDRUMS_SOURCE_DRUMKIT_KIT_H_

#include <string>
#include <vector>

namespace DrumKit
{

	struct Drum
	{

		int id;

		std::string drumName;
		std::string soundFile;

		std::vector<float> curve;

		unsigned int scanTime;
		short threshold;
		int maskTime;

	};

	struct SoundParams
	{
		short*			data;
		int 			id;
		unsigned int	length;

	};

	struct Kit
	{

		std::string kitName;
		std::string kitFolder;

		std::vector<Drum> drum;

	};

}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_KIT_H_ */
