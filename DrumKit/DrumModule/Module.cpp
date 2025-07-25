/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */


#include "Module.h"

#include "../../IO/MIDIFactory.h"
#include "../../Util/ErrorHandling.h"
#include "../../Util/Threading.h"

#include "../Kits/KitManager.h"
#include "../Triggers/TriggerFactory.h"
#include "../Triggers/TriggerManager.h"

#include "MIDIProcessor.h"
#include "TrigSound.h"

#include <algorithm>
#include <chrono>

using namespace Sound;
using namespace Util;

namespace DrumKit
{

    Module::Module(std::string dir, const AlsaParams& alsaParams, std::shared_ptr<Mixer> mixer, std::shared_ptr<Metronome> metro)
    : directory{ dir }, kitManager{ dir + "Kits/" }, kitId{ 0 }, isPlay{ false },
      soundBank{ std::make_shared<SoundBank>(dir) }, mixer{ mixer }, metronome{ metro }, metronomeSoundId{ -1 },
      isMetronomeEnabled{ false }, recorder{ soundBank.get(), alsaParams }
    {

        mixer->SetSoundBank(soundBank);

        // Load Triggers
        LoadTriggers();

        // Load all drum kits
        LoadKits();

        // Select current kit
        SelectKit(kitId);

        // Set recorder
        recorder.SetDirectory(dir);
        recorder.SetMetronomeTimeFunc([&] { return GetLastClickTime(); });
    }

    Module::~Module()
    {
        isPlay.store(false);

        // Join all threads
        if (playThread.joinable())
        {
            playThread.join();
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

        // Uncomment if debugging under Linux
        // pthread_setname_np(playThread.native_handle(), "Module Thread\0");
    }


    void Module::Stop()
    {

        isPlay.store(false);
        playThread.join();

        mixer->Clear();
    }

    void Module::EnableRecording(bool record)
    {
        if (record)
        {
            recorder.Start();
        }
        else
        {
            recorder.Stop();
        }
    }

    void Module::RecorderExport(const std::string& fileName)
    {
        recorder.Export(fileName);
    }

    void Module::RecorderExportPCM(const std::string& fileName)
    {
        recorder.ExportPCM(fileName);
    }

    void Module::RecorderPurgeTempFile()
    {
        recorder.PurgeTempFile();
    }

    void Module::GetDirectory(std::string& dir) const noexcept
    {

        dir = this->directory;
    }


    void Module::SelectKit(std::size_t id)
    {

        if (id > kits.size())
        {
            throw Util::Exception("This drum kit does not exist.", Util::errorType::error_type_error);
        }

        // Disable previous kit if it exists
        if (kitId < kits.size())
        {
            kits[kitId].Disable();
        }

        // Clear sound bank and mixer
        mixer->Clear();
        soundBank->Clear();

        // Update kit id
        kitId = id;

        // Enable new kit
        kits[kitId].Enable();

        if (isMetronomeEnabled.load())
        {
            EnableMetronome(true);
        }
    }

    std::vector<std::string> Module::GetKitsNames() const noexcept
    {

        std::vector<std::string> names;
        std::ranges::transform(kits, std::back_inserter(names), [](const Kit& k) { return k.GetName(); });

        return names;
    }

    std::vector<std::string> Module::GetInstrumentsNames() const
    {

        const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();

        std::vector<std::string> names;
        std::ranges::transform(instruments, std::back_inserter(names), [](const InstrumentPtr i) { return i->GetName(); });

        return names;
    }

    void Module::SetInstrumentVolume(size_t id, float volume)
    {
        if (kitId >= kits.size())
        {
            throw Exception("Could not set instrument volume: kit does not exist.", error_type_warning);
        }

        kits[kitId].SetInstrumentVolume(id, volume);
    }

    float Module::GetInstrumentVolume(int id) const
    {
        if (kitId >= kits.size())
        {
            throw Exception("Could not get instrument volume: kit does not exist.", error_type_warning);
        }

        return kits[kitId].GetInstrumentVolume(id);
    }

    std::vector<int> Module::GetInstrumentTriggersIds(int id) const
    {
        const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();
        auto const& instrument = instruments[id];
        return instrument->GetTriggersIds();
    }

    void Module::SaveKitConfig(std::size_t id) const
    {
        if (id < kits.size())
        {
            kits[id].Save();
        }
        else
        {
            throw Exception("Could not save kit configuration: this kit does not exist.", error_type_warning);
        }
    }

    std::string Module::GetKitLocation() const
    {
        if (kitId < kits.size())
        {
            return kits[kitId].GetConfigFilePath();
        }
        else
        {
            throw Exception("Selected kit's path could not be found.", error_type_error);
        }
    }

    bool Module::DeleteKit(const int& id)
    {

        bool isSuccess = kitManager.DeleteKit(id);

        if (isSuccess)
        {
            LoadKits();
        }

        return isSuccess;
    }

    void Module::ReloadKits()
    {
        kitManager.ReScan();
        LoadKits();
    }

    void Module::ReloadTriggers()
    {
        LoadTriggers();
    }

    float Module::GetTriggerValue(size_t id) const
    {
        if (id >= triggers.size())
        {
            throw Exception("Trigger not found.", error_type_error);
        }

        return triggers[id]->GetLastTrigValue();
    }

    void Module::EnableMetronome(bool enable)
    {

        if (enable)
        {
            metronome->GenerateClick();
            std::vector<short> data = metronome->GetData();

            metronomeSoundId = soundBank->AddSound(data, 1.0F);
            soundBank->LoopSound(metronomeSoundId, true);
            mixer->PlaySound(metronomeSoundId, 1.0F);

            isMetronomeEnabled.store(true);
        }
        else
        {

            if (metronomeSoundId != -1)
            {
                // Stop metronome sound
                mixer->StopSound(metronomeSoundId);
                soundBank->DeleteSound(metronomeSoundId);
            }

            isMetronomeEnabled.store(false);
        }
    }

    void Module::ChangeTempo(int tempo)
    {
        metronome->SetTempo(tempo);
        RestartMetronome();
    }

    void Module::ChangeClickVolume(int volume)
    {
        if (isMetronomeEnabled.load())
        {
            soundBank->SetSoundVolume(metronomeSoundId, float(volume / 100.0F));
        }
    }

    float Module::GetClickVolume() const noexcept
    {
        if (metronomeSoundId != -1)
        {
            return soundBank->GetSound(metronomeSoundId).GetVolume();
        }
        else
        {
            return 0.0F;
        }
    }


    double Module::GetClickPosition() const noexcept
    {

        if (isMetronomeEnabled.load())
        {
            unsigned long pos = soundBank->GetSound(metronomeSoundId).LoadIndex();
            double relPos = double(pos) / double(soundBank->GetSound(metronomeSoundId).GetLength());
            // fraction -= int(fraction);

            return relPos;
        }
        else
        {
            return 0.0F;
        }
    }

    int64_t Module::GetLastClickTime() const noexcept
    {

        if (isMetronomeEnabled.load())
        {
            return soundBank->GetSound(metronomeSoundId).GetLastStartTime();
        }
        else
        {
            return 0;
        }
    }

    std::vector<IO::SpiDevParameters> Module::GetSpiDevParams() const
    {
        std::vector<IO::SpiDevParameters> spiDevParams;
        spiDevParams.reserve(spidev.size());
        std::ranges::transform(spidev, std::back_inserter(spiDevParams), [](const auto& spidev)
                               { return IO::SpiDevParameters{ spidev->GetName(), spidev->GetBus(), spidev->GetCS() }; });
        return spiDevParams;
    }

    void Module::RestartMetronome()
    {
        if (isMetronomeEnabled.load())
        {
            EnableMetronome(false);
            EnableMetronome(true);
        }
    }


    // PRIVATE METHODS

    void Module::LoadKits()
    {

        // Clear kits list
        kits.clear();

        // Get all kits locations
        std::vector<std::string> kitsPaths = kitManager.GetKitsLocations();

        std::ranges::transform(kitsPaths, std::back_inserter(kits),
                               [this](std::string const& kitPath)
                               {
                                   KitParameters kitParams;
                                   KitManager::LoadKit(kitPath, kitParams);

                                   return Kit(kitParams, this->triggers, this->soundBank);
                               });
    }

    void Module::LoadTriggers()
    {

        // Update sensors configuration
        TriggerManager::LoadSensorsConfig(this->directory, this->sensorsConfig);

        // if(sensorsConfig.sensorType == "Spi")
        {
            TriggerManager::LoadSpiDevConfig(this->directory, this->spidev);
            this->sensorFactory.SetSpiDev(this->spidev);
        }


        this->sensorFactory.SetDataFolder(this->sensorsConfig.hddDataFolder);

        // Load triggers
        TriggerManager::LoadTriggersConfig(this->directory, sensorsConfig, this->triggersParameters);
        // TriggerManager::SaveTriggersConfig(this->directory, this->triggersParameters);

        // Create Triggers
        this->CreateTriggers(this->triggersParameters);
    }


    void Module::Run()
    {
        using namespace std::chrono;

        if (sensorsConfig.sensorType == "Spi")
        {
            for (auto& dev : spidev)
            {
                dev->Close();
                dev->Open(sensorsConfig.samplingRate, 0);
            }
        }


        if (isMetronomeEnabled.load())
        {
            const auto metronomeVolume = GetClickVolume();
            mixer->PlaySound(metronomeSoundId, metronomeVolume);
        }

        lastTrigTime.store(0, std::memory_order_relaxed);
        lastTrigValue.store(0, std::memory_order_relaxed);

        // Skip high-pass filter transient state
        for (size_t i = 0; i < triggers.size() * 100; ++i)
        {
            std::ranges::for_each(triggers, [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });
        }


        if (sensorsConfig.sensorType.contains("Midi"))
        {

            auto midi = IO::MIDIFactory::Make(sensorsConfig.sensorType);
            midi->SetPort(sensorsConfig.sensorType == "SerialMidi" ? sensorsConfig.serialPort : sensorsConfig.midiPort);
            midi->SetBaudRate(sensorsConfig.samplingRate);
            midi->Open();

            while (isPlay.load())
            {
                const auto message = midi->GetMessage();

                if (message)
                {
                    if (!MIDIProcessor::ValidateCommand(message->command))
                    {
                        continue;
                    }

                    const auto instruments = kits[kitId].GetInstruments();

                    for (const auto& instrument : instruments)
                    {
                        const auto instrumentSoundId = instrument->GetSoundIdFromMidiParams(message.value());

                        if (instrumentSoundId)
                        {
                            // std::cout << *instrumentSoundId << std::endl;
                            const auto volume = static_cast<float>(message->param2) / 127.F;

                            lastTrigValue.store(100.F * volume, std::memory_order_release);

                            const auto now = high_resolution_clock::now();
                            const auto t = static_cast<int64_t>(time_point_cast<microseconds>(now).time_since_epoch().count());

                            lastTrigTime.store(t, std::memory_order_release);

                            if (recorder.IsRecording(std::memory_order_relaxed))
                            {
                                recorder.Push(TrigSound{ .instrumentId = instrument->GetId(),
                                                         .soundId = instrumentSoundId.value(),
                                                         .timeStamp = t,
                                                         .volume = volume });
                            }
                            mixer->PlaySound(*instrumentSoundId, volume);
                        }
                    }
                }
            }
        }
        else
        {
            while (isPlay.load())
            {
                // Refresh triggers
                std::ranges::for_each(triggers, [](TriggerPtr& triggerPtr) { triggerPtr->Refresh(); });

                // Get most recent hit
                auto it =
                std::ranges::max_element(triggers, [](const TriggerPtr& t1, const TriggerPtr& t2)
                                         { return t1->GetTriggerState().trigTime < t2->GetTriggerState().trigTime; });


                int64_t trigTime = (*it)->GetTriggerState().trigTime;
                int64_t prevTrigTime = lastTrigTime.exchange(trigTime, std::memory_order_release);

                if (prevTrigTime != trigTime)
                {
                    lastTrigValue.store(int((*it)->GetTriggerState().value * 100.0F), std::memory_order_release);

                    // std::cout << double(trigTime - soundBank->GetSound(metronomeSoundId).GetLastStartTime()) / 1000. << std::endl;
                }

                // Check instruments triggers and send sounds to mixer if necessary
                const std::vector<InstrumentPtr>& instruments = kits[kitId].GetInstruments();
                for (const InstrumentPtr& instrumentPtr : instruments)
                {

                    bool isTriggerEvent = instrumentPtr->IsTriggerEvent();

                    if (isTriggerEvent)
                    {
                        int soundId = 0;
                        float volume = 1.0F;
                        instrumentPtr->GetSoundProps(soundId, volume);

                        if (recorder.IsRecording(std::memory_order_relaxed))
                        {
                            recorder.Push(TrigSound{
                            .instrumentId = instrumentPtr->GetId(), .soundId = soundId, .timeStamp = trigTime, .volume = volume });
                        }

                        mixer->PlaySound(soundId, volume);
                    }
                }
            }
        }
    }


    void Module::CreateTriggers(const std::vector<TriggerParameters>& triggersParameters)
    {

        triggers.clear();

        for (const TriggerParameters& triggerParameters : triggersParameters)
        {
            TriggerPtr triggerPtr = TriggerFactory::CreateTrigger(triggerParameters, this->sensorFactory);
            triggers.push_back(std::move(triggerPtr));
        }
    }
} // namespace DrumKit
