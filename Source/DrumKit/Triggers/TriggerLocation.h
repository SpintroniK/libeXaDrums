/*
 * TriggerLocation.h
 *
 *  Created on: 8 Mar 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_

#include <string>
#include <sstream>

namespace DrumKit
{

	enum class TriggerLocation
	{

		DrumHead,
		Rim,

		First = DrumHead,
		Last = Rim

	};



	std::ostream& operator<<(std::ostream& o, const TriggerLocation& x);

	TriggerLocation operator++(TriggerLocation& x);
	TriggerLocation operator*(TriggerLocation t);
	TriggerLocation begin(TriggerLocation x);
	TriggerLocation end(TriggerLocation x);

}


#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERLOCATION_H_ */
