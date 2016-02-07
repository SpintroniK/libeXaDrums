/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_
#define LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_

#include "../IO/SensorType.h"
#include "../Sound/Alsa/Alsa.h"
#include "../Sound/Alsa/AlsaParameters.h"
#include "../Sound/Mixer.h"
#include "../Sound/SoundProcessor/SoundProcessor.h"
#include "../DrumKit/DrumModule/Module.h"
#include "../DrumKit/KitManager/KitManager.h"

#include <string>
#include <vector>
#include <memory>

namespace eXaDrumsApi
{

	class eXaDrums
	{

	public:

		//eXaDrumKit();
		eXaDrums(const char* dataLocation, IO::SensorType sensorType);
		~eXaDrums();

		void LoadKit(const char* kitLocation);
		void CreateKitManager(const char* kitsPath);

		//
		void Start();
		void Stop();

	private:


		std::unique_ptr<DrumKit::Module> drumModule;

		std::unique_ptr<DrumKit::KitManager> kitManager;

		Sound::AlsaParams alsaParams;
		std::unique_ptr<Sound::Alsa> alsa;
		std::shared_ptr<Sound::Mixer> mixer;
		std::shared_ptr<Sound::SoundProcessor> soundProc;


	};


}

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
