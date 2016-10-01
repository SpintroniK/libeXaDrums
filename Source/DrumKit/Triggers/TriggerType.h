/*
 * TriggerType.h
 *
 *  Created on: 6 Mar 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_TRIGGERS_TRIGGERTYPE_H_
#define SOURCE_DRUMKIT_TRIGGERS_TRIGGERTYPE_H_

#include <sstream>
#include <string>

namespace DrumKit
{

	enum class TriggerType
	{

		Discrete,
		Continuous,

		First = Discrete,
		Last = Continuous

	};


	inline std::ostream& operator<<(std::ostream& o, const TriggerType& x)
	{

		std::string os;

		switch (x)
		{

		case TriggerType::Discrete:		os = "Discrete";	break;
		case TriggerType::Continuous:	os = "Continuous";	break;


		default: break;

		}

		return o << os;
	}

	inline TriggerType operator++(TriggerType& x) { return x = (TriggerType)(std::underlying_type<TriggerType>::type(x) + 1); };
	inline TriggerType operator*(TriggerType x) { return x; };
	inline TriggerType begin(TriggerType x) { return TriggerType::First; };
	inline TriggerType end(TriggerType x) { TriggerType l = TriggerType::Last; return ++l; };


}



#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERTYPE_H_ */
