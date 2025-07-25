/*
 * Drum.h
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_DRUMKIT_DRUMMODULE_MODULE_H
#define LIBEXADRUMS_DRUMKIT_DRUMMODULE_MODULE_H

#include "../../IO/SensorFactory.h"
#include "../../IO/SensorsConfig.h"
#include "../../IO/SpiDevices/SpiDevParameters.h"
#include "../../Metronome/Metronome.h"
#include "../../Sound/Alsa/AlsaParams.h"
#include "../../Sound/Mixer/Mixer.h"
#include "../../Sound/SoundBank/SoundBank.h"

#include "../Kits/Kit.h"

#include "Recorder.h"

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>


namespace DrumKit
{

    class Module
    {

    public:
        Module(const Module&) = delete;
        Module(Module&&) = delete;
        Module& operator=(const Module&) = delete;
        Module& operator=(Module&&) = delete;
        Module(std::string dir, const Sound::AlsaParams& alsaParams, std::shared_ptr<Sound::Mixer> mixer, std::shared_ptr<Metronome> metro);
        virtual ~Module();

        // Kit
        void SaveKitConfig(std::size_t id) const;
        std::string GetKitLocation() const;
        bool DeleteKit(const int& id);
        void SelectKit(std::size_t id);
        void ReloadKits();
        std::size_t GetKitId() const noexcept
        {
            return kitId;
        }
        std::size_t GetNumKits() const noexcept
        {
            return kits.size();
        };
        std::vector<std::string> GetKitsNames() const noexcept;
        std::vector<std::string> GetInstrumentsNames() const;

        // Instrument
        void SetInstrumentVolume(size_t id, float volume);
        float GetInstrumentVolume(int id) const;
        int GetNumInstruments() const
        {
            return kits[kitId].GetNumInstruments();
        };
        std::vector<int> GetInstrumentTriggersIds(int id) const;

        // Triggers
        void ReloadTriggers();
        void SetTriggerParameters(int triggerId, const TriggerParameters& params)
        {
            triggers[triggerId]->SetParameters(params);
        }
        void SetTriggerSensorValue(int id, short data)
        {
            triggers[id]->SetSensorData(data);
        }
        std::vector<TriggerParameters> GetTriggersParameters() const
        {
            return this->triggersParameters;
        }
        unsigned long long GetLastTrigTime() const noexcept
        {
            return lastTrigTime.load(std::memory_order_acquire);
        }
        int GetLastTrigValue() const noexcept
        {
            return lastTrigValue.load(std::memory_order_acquire);
        }
        float GetTriggerValue(size_t id) const;

        // Module
        void Start();
        void Stop();
        void EnableRecording(bool record);
        void RecorderExport(const std::string& fileName);
        void RecorderExportPCM(const std::string& fileName);
        void RecorderPurgeTempFile();
        void GetDirectory(std::string& dir) const noexcept;

        // Metronome
        void EnableMetronome(bool enable);
        void ChangeTempo(int tempo);
        void ChangeClickVolume(int volume);
        float GetClickVolume() const noexcept;
        void RestartMetronome();
        double GetClickPosition() const noexcept;
        int64_t GetLastClickTime() const noexcept;

        // Config
        IO::SensorsConfig GetSensorsConfig() const noexcept
        {
            return sensorsConfig;
        }
        std::vector<IO::SpiDevParameters> GetSpiDevParams() const;

    private:
        void LoadKits();
        void LoadTriggers();
        void Run();
        void CreateTriggers(const std::vector<TriggerParameters>& trigParams);
        bool IsMetronomeEnabled() const;

        IO::SensorFactory sensorFactory;
        std::vector<IO::SpiDevPtr> spidev;

        // Module
        std::string directory;
        std::thread playThread;

        // Kits
        KitManager kitManager;
        std::size_t kitId;
        std::vector<Kit> kits;
        std::atomic<bool> isPlay;

        // Triggers
        std::vector<TriggerParameters> triggersParameters;
        std::vector<TriggerPtr> triggers;
        std::atomic<int64_t> lastTrigTime;
        std::atomic<int> lastTrigValue;

        IO::SensorsConfig sensorsConfig;

        // Sound
        std::shared_ptr<Sound::SoundBank> soundBank;
        std::shared_ptr<Sound::Mixer> mixer;
        std::shared_ptr<Metronome> metronome;

        int metronomeSoundId;
        std::atomic<bool> isMetronomeEnabled;

        Recorder recorder;
    };

} // namespace DrumKit

#endif /* LIBEXADRUMS_DRUMKIT_DRUMMODULE_MODULE_H */
