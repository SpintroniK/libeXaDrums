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


	struct SoundParams
	{
		std::vector<short>	data;
		int 				id;
		unsigned int		length;

	};


}

#endif /* RASPIDRUMS_SOURCE_DRUMKIT_KIT_H_ */
