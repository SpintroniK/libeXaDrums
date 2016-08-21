/*
 * eXaDrumsApi.h
 *
 *  Created on: 8 Sep 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_
#define LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_

#include "../Sound/Alsa/Alsa.h"
#include "../Sound/Alsa/AlsaParameters.h"
#include "../Sound/Mixer/Mixer.h"
#include "../DrumKit/DrumModule/Module.h"
#include "../DrumKit/Kits/KitManager.h"

#include <string>
#include <vector>
#include <memory>
#include <atomic>

namespace eXaDrumsApi
{

	class eXaDrums
	{

	public:

		//eXaDrumKit();
		eXaDrums(const char* dataLocation);
		~eXaDrums();

		void SelectKit(int id);
		bool IsStarted() const { return isStarted; }

		//
		void Start();
		void Stop();

		// Kits
		int GetNumKits() const { return drumModule->GetNumKits(); }
		void GetKitNameById(int id, char* kitName, int& nameLength);

		// Instruments
		int GetNumInstruments() const { return drumModule->GetNumInstruments(); }
		void GetInstrumentName(int id, char* name, int& nameLength);

	private:

		void CppStringToC(std::string input, char* str, int& length) const;

		std::unique_ptr<DrumKit::Module> drumModule;

		Sound::AlsaParams alsaParams;
		std::unique_ptr<Sound::Alsa> alsa;
		std::shared_ptr<Sound::Mixer> mixer;

		std::atomic<bool> isStarted;


	};


}

#endif /* LIBEXADRUMS_SOURCE_API_EXADRUMKIT_H_ */
