/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMKIT_H_
#define SOURCE_API_EXADRUMKIT_H_

#include "../DrumKit/Module.h"
#include "../Sound/Alsa.h"
#include "../Sound/Mixer.h"

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


		DrumKit::Module drumModule;
		DrumKit::Kit kit;

		Sound::AlsaParams alsaParams;
		Sound::Alsa* alsa;

		Sound::Mixer* mixer;

	};


}

#endif /* SOURCE_API_EXADRUMKIT_H_ */
