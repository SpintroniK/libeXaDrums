/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */


#include "Module.h"

#include "../../IO/Spi.h"
#include "../../Util/Threading.h"

#include "../Triggers/TriggerManager.h"
#include "../Triggers/TriggerFactory.h"
#include "../Kits/KitManager.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace Sound;

namespace DrumKit
{

	Module::Module(std::string dir, std::shared_ptr<Mixer> mixer, std::shared_ptr<Metronome> metro)
	: directory(dir), isRecord{false},
	  kitManager(dir + "Kits/"),  kitId(0),
	  isPlay(false),
	  mixer(mixer),
	  metronome(metro), metronomeSoundId(-1), isMetronomeEnabled(false)
	{

		this->soundBank = std::make_shared<SoundBank>(dir);

		mixer->SetSoundBank(soundBank);

		// Load Triggers
		LoadTriggers();

		// Load all drum kits
		LoadKits();

		// Select current kit
		SelectKit(kitId);

		return;
	}

	Module::~Module()
	{

		isPlay.store(false);
		isRecord.store(false, std::memory_order_relaxed);

		// Join all threads
		if(playThread.joinable())
		{
			playThread.join();
		}

		if(recordThread.joinable())
		{
			recordThread.join();
		}

	}

	void Module::Start()
	{

		isPlay.store(true);
		playThread = std::thread(&Module::Run, this);

		// Set high priority to the thread
//		int maxPriority = sched_get_priority_max(SCHED_FIFO);
//
//		if(maxPriority > 1)
//		{
//			maxPriority--;
//		}
//
//		sched_param sch_params;
//		sch_params.sched_priority = maxPriority;
//
//		pthread_setschedparam(playThread.native_handle(), SCHED_FIFO, &sch_params);

		Util::SetThreadPriority(playThread.native_handle(), 99);

		return;
	}


	void Module::Stop()
	{

		isPlay.store(false);
		playThread.join();

		mixer->Clear();

		return;
	}

	void Module::EnableRecording(bool record)
	{

		isRecord.store(record, std::memory_order_release);

		if(record)
		{
			recordThread = std::thread(&Module::Record, this);
		}
		else
		{
			recordThread.join();
		}

	}

	void Module::GetDirectory(std::string& dir) const
	{

		dir = this->directory;

		return;
	}


	void Module::SelectKit(std::size_t id)
	{

		if(id > kits.size())
		{
			std::cerr << "Error: there is no kit with the id " << id << std::endl;
			throw -1;
		}

		// Disable previous kit
		kits[kitId].Disable();

		// Clear sound bank and mixer
		mixer->Clear();
		soundBank->Clear();

		// Update kit id
		kitId = id;

		// Enable new kit
		kits[kitId].Enable();

		if(isMetronomeEnabled)
		{
			EnableMetronome(true);
		}


		return;
	}

	std::vector<std::string> Module::GetKitsNames() const
	{

		std::vector<std::string> names;
		std::transform(kits.cbegin(), kits.cend(), std::back_inserter(names), [](const Kit& k) { return k.GetName(); });

		return names;
	}

	std::vector<std::string> Module::GetInstrumentsNames() const
	{

		const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();

		std::vector<std::string> names;
		std::transform(instruments.cbegin(), instruments.cend(), std::back_inserter(names), [](const InstrumentPtr i) { return i->GetName(); });

		return names;
	}


	bool Module::DeleteKit(const int& id)
	{

		bool isSuccess = kitManager.DeleteKit(id);

		if(isSuccess)
		{
			LoadKits();
		}

		return isSuccess;
	}

	void Module::ReloadKits()
	{

		kitManager.ReScan();
		LoadKits();

		return;
	}

	void Module::ReloadTriggers()
	{

		LoadTriggers();

		return;
	}

	void Module::EnableMetronome(bool enable)
	{

		if(enable)
		{
			metronome->GenerateClick();
			std::vector<short> data = metronome->GetData();

			metronomeSoundId = soundBank->AddSound(data, 0.5f);
			soundBank->LoopSound(metronomeSoundId, true);
			mixer->PlaySound(metronomeSoundId, 1.0f);

			isMetronomeEnabled = true;
		}
		else
		{

			if(metronomeSoundId != -1)
			{
				// Stop metronome sound
				mixer->StopSound(metronomeSoundId);
				soundBank->DeleteSound(metronomeSoundId);
			}

			isMetronomeEnabled = false;
		}


		return;
	}

	void Module::ChangeTempo(int tempo)
	{

		metronome->SetTempo(tempo);
		RestartMetronome();

		return;
	}

	void Module::ChangeVolume(int volume)
	{

		if(isMetronomeEnabled)
		{
			soundBank->SetSoundVolume(metronomeSoundId, float(volume / 100.0f));
		}

		return;
	}

	float Module::GetClickVolume() const
	{
		return soundBank->GetSound(metronomeSoundId).GetVolume();
	}


	double Module::GetClickPosition() const
	{

		if(isMetronomeEnabled)
		{
			unsigned long pos = soundBank->GetSound(metronomeSoundId).LoadIndex();
			double relPos = double(pos) / double(soundBank->GetSound(metronomeSoundId).GetLength());
			//fraction -= int(fraction);

			return relPos;
		}
		else
		{
			return 0.0f;
		}
	}

	int64_t Module::GetLastClickTime() const
	{

		if(isMetronomeEnabled)
		{
			return soundBank->GetSound(metronomeSoundId).GetLastStartTime();
		}
		else
		{
			return 0;
		}
	}

	void Module::RestartMetronome()
	{

		if(isMetronomeEnabled)
		{
			EnableMetronome(false);
			EnableMetronome(true);
		}

		return;
	}


	// PRIVATE METHODS

	void Module::LoadKits()
	{

		// Clear kits list
		kits.clear();

		// Get all kits locations
		std::vector<std::string> kitsPaths = kitManager.GetKitsLocations();

		std::transform(kitsPaths.cbegin(), kitsPaths.cend(), std::back_inserter(kits), [this](std::string const& kitPath)
		{
			KitParameters kitParams;
			KitManager::LoadKit(kitPath, kitParams);

			return Kit(kitParams, this->triggers, this->soundBank);
		});

		return;
	}

	void Module::LoadTriggers()
	{

		// Update sensors configuration
		TriggerManager::LoadSensorsConfig(this->directory, this->sensorsConfig);

		if(sensorsConfig.sensorType == IO::SensorType::Spi)
		{
			IO::Spi::get().Close();
			IO::Spi::get().Open(sensorsConfig.samplingRate, 0);
		}


		// Load triggers
		TriggerManager::LoadTriggersConfig(this->directory, sensorsConfig, this->triggersParameters);

		TriggerManager::SaveTriggersConfig(this->directory, this->triggersParameters);

		// Create Triggers
		this->CreateTriggers(this->triggersParameters);

		return;
	}


	void Module::Run()
	{

		if(isMetronomeEnabled)
		{
			mixer->PlaySound(metronomeSoundId, 1.0f);
		}

		lastTrigTime.store(0, std::memory_order_relaxed);
		lastTrigValue.store(0, std::memory_order_relaxed);

		while(isPlay.load())
		{

			// Refresh triggers
			std::for_each(triggers.begin(), triggers.end(), [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });

			// Get most recent hit
			auto it = std::max_element(triggers.cbegin(), triggers.cend(),
					[](const TriggerPtr& t1, const TriggerPtr& t2) { return t1->GetTriggerState().trigTime < t2->GetTriggerState().trigTime; });


			int64_t trigTime = (*it)->GetTriggerState().trigTime;
			int64_t prevTrigTime = lastTrigTime.exchange(trigTime, std::memory_order_release);

			if(prevTrigTime != trigTime)
			{
				lastTrigValue.store(int((*it)->GetTriggerState().value * 100.0f), std::memory_order_release);

				//std::cout << double(trigTime - soundBank->GetSound(metronomeSoundId).GetLastStartTime()) / 1000. << std::endl;

			}



			// Check instruments triggers and send sounds to mixer if necessary
			const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();
			for(const InstrumentPtr& instrumentPtr : instruments)
			{

				bool isTriggerEvent = instrumentPtr->IsTriggerEvent();

				if(isTriggerEvent)
				{
					int soundId = 0;
					float volume = 1.0f;
					instrumentPtr->GetSoundProps(soundId, volume);

					if(isRecord.load(std::memory_order_relaxed))
					{
						recordQueue.Push({soundId, volume, trigTime});
					}

					mixer->PlaySound(soundId, volume);
				}
			}
		}

		return;
	}

	void Module::Record()
	{

		using namespace Util;
		using namespace std::chrono_literals;
		using namespace std::chrono;
		using namespace std::this_thread;

		using TrigSound = std::tuple<int, float, int64_t>;

		// Create new file
		const auto fileTimeStamp = system_clock::now().time_since_epoch().count();
		const std::string fileName = directory + "Rec/" + std::to_string(fileTimeStamp) + ".csv";

		std::queue<TrigSound> buffer;

		std::ofstream file{fileName};

		auto dumpBufferToFile = [&]()
			{
				while(!buffer.empty())
				{
					int soundId;
					float volume;
					int64_t time;
					std::tie(soundId, volume, time) = buffer.front();
					buffer.pop();

					file << soundId << ',' << time << ',' << volume << '\n';
				}

				// Insert keyframe if the metronome is running
				if(isMetronomeEnabled)
				{
					file << -1 << ',' << GetLastClickTime() << ',' << 0.5f << '\n';
				}

				file.flush();
			};

		while(isRecord.load(std::memory_order_acquire))
		{

			TrigSound trigSound;

			while(recordQueue.Pop(trigSound))
			{
				buffer.emplace(std::move(trigSound));
			}

			// Write data to file
			if(buffer.size() >= recordQueue.Capacity() / 8)
			{
				dumpBufferToFile();
			}

			// Wait before we try to get more sounds
			if(isRecord.load(std::memory_order_relaxed))
			{
				sleep_for(500ms);
			}

		}

		dumpBufferToFile();

	}

	void Module::CreateTriggers(const std::vector<TriggerParameters>& triggersParameters)
	{


		triggers.clear();

		for(const TriggerParameters& triggerParameters : triggersParameters)
		{

			TriggerPtr triggerPtr = TriggerFactory::CreateTrigger(triggerParameters);

			triggers.push_back(triggerPtr);

		};


		return;
	}

}

