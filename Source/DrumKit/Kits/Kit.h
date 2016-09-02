/*
 * Kit.h
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_KITS_KIT_H_
#define SOURCE_DRUMKIT_KITS_KIT_H_

#include "KitParameters.h"

#include "../../Sound/SoundBank/SoundBank.h"

#include "../Instruments/InstrumentParameters.h"
#include "../Instruments/Instrument.h"
#include "../Instruments/Drums/TestDrum.h"
#include "../Triggers/TriggerType.h"
#include "../Triggers/Trigger.h"
#include "../Triggers/DiscreteTrigger.h"

#include <string>


namespace DrumKit
{

	class Kit
	{

		public:

			Kit(KitParameters params, std::vector<TriggerPtr> const& trigs, std::shared_ptr<Sound::SoundBank> sb);
			virtual ~Kit();

			void Enable();
			void Disable();

			void SetInstrumentVolume(int id, float volume) { this->instruments[id]->SetVolume(volume); }

			std::string GetInstrumentName(std::size_t id) const;
			std::string GetName() const { return parameters.kitName; }
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
