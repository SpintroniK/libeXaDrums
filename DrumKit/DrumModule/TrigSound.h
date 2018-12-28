/*
 * TrigSound.h
 *
 *  Created on: 3 Mar 2018
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_DRUMMODULE_TRIGSOUND_H_
#define SOURCE_DRUMKIT_DRUMMODULE_TRIGSOUND_H_

#include <cstdint>

namespace DrumKit
{

	struct TrigSound
	{

		int instrumentId;
		int soundId;
		int64_t timeStamp;
		float volume;

	};


}

#endif /* SOURCE_DRUMKIT_DRUMMODULE_TRIGSOUND_H_ */
