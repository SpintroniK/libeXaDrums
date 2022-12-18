/*
 * InstrumentSoundInfo.h
 *
 *  Created on: 15 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTSOUNDINFO_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTSOUNDINFO_H_


#include "../../Sound/InstrumentSoundType.h"

#include <string>


namespace DrumKit
{

	struct InstrumentSoundInfo
	{

		int id;
		std::string soundLocation;
		Sound::InstrumentSoundType type;
		uint8_t midiNote{};


	};


}


#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTSOUNDINFO_H_ */
