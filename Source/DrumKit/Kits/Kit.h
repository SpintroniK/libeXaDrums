/*
 * Kit.h
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KIT_H_
#define SOURCE_DRUMKIT_KITS_KIT_H_

#include "KitParameters.h"

#include <string>

class Module;

namespace DrumKit
{

	class Kit
	{

		//xxx To be removed
		friend class Module;

		public:

			Kit(KitParameters params);
			virtual ~Kit();

			std::string GetInstrumentName(std::size_t id) const;
			std::string GetName() const { return parameters.kitName; }
			int GetNumInstruments() const { return (int)parameters.instrumentParameters.size(); }

		private:

			KitParameters parameters;


	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KIT_H_ */
