/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMKIT_H_
#define SOURCE_API_EXADRUMKIT_H_

#include "../DrumKit/Trigger.h"
#include "../DrumKit/Module.h"
#include "../Sound/Alsa.h"
#include "../Sound/Mixer.h"

#include <string>
#include <vector>
#include <memory>

namespace eXaDrumKitApi
{

	class eXaDrumKit
	{

	public:

		eXaDrumKit();
		eXaDrumKit(const char* dataLocation);
		~eXaDrumKit();

		void LoadKit(const char* kitLocation);

		// Trigger stuff
		size_t AddTrigger(size_t drumId);
		void Trig(size_t triggerId, short value);

		//
		void Start();
		void Stop();

	private:


		DrumKit::Module drumModule;
		DrumKit::Kit kit;

		Sound::AlsaParams alsaParams;
		std::unique_ptr<Sound::Alsa> alsa;

		std::unique_ptr<Sound::Mixer> mixer;

		std::vector<std::unique_ptr<DrumKit::Trigger>> triggers;

	};


}

#endif /* SOURCE_API_EXADRUMKIT_H_ */
