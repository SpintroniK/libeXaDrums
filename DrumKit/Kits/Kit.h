/*
 * Kit.h
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KIT_H_
#define SOURCE_DRUMKIT_KITS_KIT_H_

#include "KitParameters.h"
#include "KitManager.h"

#include "../../Sound/SoundBank/SoundBank.h"

#include "../Instruments/Instrument.h"
#include "../Triggers/Triggers/Trigger.h"

#include <string>
#include <vector>


namespace DrumKit
{

	class Kit
	{

		public:

			Kit(const KitParameters& params, std::vector<TriggerPtr> const& trigs, std::shared_ptr<Sound::SoundBank> sb);
			virtual ~Kit();

			void Enable();
			void Disable();
			void Save() const { KitManager::SaveKit(parameters.configFilePath, parameters);}

			void SetInstrumentVolume(size_t id, float volume);

			std::string GetConfigFilePath() const noexcept { return parameters.configFilePath; }
			float GetInstrumentVolume(int id) const { return instruments[id]->GetVolume(); }
			std::string GetInstrumentName(std::size_t id) const;
			std::string GetName() const noexcept { return parameters.kitName; }
			int GetNumInstruments() const { return (int)parameters.instrumentParameters.size(); }
			const std::vector<InstrumentPtr>& GetInstruments() const { return instruments; }



		private:

			void CreateInstruments();

			KitParameters parameters;

			const std::vector<TriggerPtr>& triggers;
			std::shared_ptr<Sound::SoundBank> soundBank;

			std::vector<InstrumentPtr> instruments;

	};

} /* namespace DrumKit */

#endif /* SOURCE_DRUMKIT_KITS_KIT_H_ */
