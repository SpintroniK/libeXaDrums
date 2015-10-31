/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMKIT_H_
#define SOURCE_API_EXADRUMKIT_H_

#include "../IO/SensorType.h"
#include "../Sound/Mixer.h"

#include <string>
#include <vector>
#include <memory>

#include "../DrumKit/DrumModule/Module.h"
#include "../Sound/Alsa/Alsa.h"

namespace eXaDrumKitApi
{

	class eXaDrumKit
	{

	public:

		eXaDrumKit();
		eXaDrumKit(const char* dataLocation);
		~eXaDrumKit();

		void LoadKit(const char* kitLocation);

		//
		void Start();
		void Stop();

	private:


		std::unique_ptr<DrumKit::Module> drumModule;
		DrumKit::Kit kit;

		Sound::AlsaParams alsaParams;
		std::unique_ptr<Sound::Alsa> alsa;
		std::shared_ptr<Sound::Mixer> mixer;


	};


}

#endif /* SOURCE_API_EXADRUMKIT_H_ */
