/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMKIT_H_
#define SOURCE_API_EXADRUMKIT_H_

#include "../DrumKit/Module.h"

#include <string>

namespace eXaDrumKitApi
{

	class eXaDrumKit
	{

	public:

		eXaDrumKit();
		eXaDrumKit(const char* dataLocation);
		~eXaDrumKit();

		void LoadKit(const char* kitLocation);

	private:

		const std::string defaultDataLoc = "./Data";

		DrumKit::Module drumModule;
		DrumKit::Kit kit;

	};


}

#endif /* SOURCE_API_EXADRUMKIT_H_ */
