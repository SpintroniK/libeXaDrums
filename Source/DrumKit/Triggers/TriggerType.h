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
#include <type_traits>

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

	inline TriggerType operator++(TriggerType& x) { return x = static_cast<TriggerType>(std::underlying_type_t<TriggerType>(x) + 1); };
	inline TriggerType operator*(TriggerType x) { return x; };
	inline TriggerType begin(TriggerType x) { return TriggerType::First; };
	inline TriggerType end(TriggerType x) { TriggerType l = TriggerType::Last; return ++l; };


	inline std::istream& operator>>(std::istream& is, TriggerType& x)
	{
		return Util::StreamToEnum(is, x);
	}

}



#endif /* SOURCE_DRUMKIT_TRIGGERS_TRIGGERTYPE_H_ */
