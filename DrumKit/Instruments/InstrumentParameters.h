/*
 * InstrumentParameters.h
 *
 *  Created on: 15 Nov 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_
#define SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_

#include "../../Util/Xml.h"
#include "../../Util/Enums.h"
#include "../Triggers/TriggerLocation.h"

#include "InstrumentSoundInfo.h"
#include "InstrumentType.h"

#include <tinyxml2.h>

#include <vector>
#include <string>
#include <utility>

namespace DrumKit
{

	struct InstrumentParameters
	{

		void ToXml(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* element)
		{
			using namespace Util;

			element->InsertEndChild(CreateXmlElement(doc, "instrumentName", instrumentName));

			// Triggers
			{
				// Create triggers element
				tinyxml2::XMLElement* triggers = CreateXmlElement(doc, "triggers", "");

				for(const auto& trigger : triggersIdsAndLocations)
				{
					triggers->InsertEndChild(CreateXmlElement(doc, "trigger", trigger.first, {{"location", Enums::ToString(trigger.second)}}));
				}

				element->InsertEndChild(triggers);
			}

			// Sounds
			{
				// Create sounds element
				tinyxml2::XMLElement* sounds = CreateXmlElement(doc, "sounds", "");

				for(const auto& sound : soundsInfo)
				{
					sounds->InsertEndChild(CreateXmlElement(doc, "sound", sound.soundLocation, {{"type", Enums::ToString(sound.type)}}));
				}

				element->InsertEndChild(sounds);
			}

		}


		InstrumentType instrumentType;

		int id;
		float volume;

		std::string instrumentName;
		std::vector<InstrumentSoundInfo> soundsInfo;
		std::vector<std::pair<int, TriggerLocation>> triggersIdsAndLocations;

	};

}

#endif /* SOURCE_DRUMKIT_INSTRUMENTS_INSTRUMENTPARAMETERS_H_ */
