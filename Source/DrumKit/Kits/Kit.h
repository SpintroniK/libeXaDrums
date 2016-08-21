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

namespace DrumKit
{

	class Kit
	{

		public:

			Kit(KitParameters params);
			virtual ~Kit();

			std::string GetName() const { return parameters.kitName; }
			KitParameters GetParameters() const { return parameters; }

		private:

			KitParameters parameters;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KIT_H_ */
