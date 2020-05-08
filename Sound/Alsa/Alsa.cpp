/*
 * Alsa.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Alsa.h"

#include "../../Util/Threading.h"
#include "../../Util/ErrorHandling.h"

#include <alsa/asoundlib.h>

#include <chrono>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include <cstring>

using namespace Util;

namespace Sound
{

	Alsa::Alsa(const AlsaParams& parameters, std::shared_ptr<Mixer> const& mix)
	: params(parameters), mixer(mix), play(false), rec(false)

	{

		_snd_pcm_stream type = (params.capture)? SND_PCM_STREAM_CAPTURE:SND_PCM_STREAM_PLAYBACK;


		int err = snd_pcm_open(&params.handle, params.device.c_str(), type, 0);

		if(err >= 0)
		{
			snd_pcm_hw_params_alloca(&params.hwParams);
			SetHwParams();

			snd_pcm_sw_params_alloca(&params.swParams);
			SetSwParams();
		}
		else
		{
			throw Exception(snd_strerror(err), error_type_error);
		}


		auto devices = GetDevices();
		auto itDev = std::find_if(devices.begin(), devices.end(), [&](const auto& d) { return d.second ==  params.device; });

		if(itDev == devices.end())
		{
			if(params.device == "default")
			{
				this->deviceName = devices.front().first;
			}
			else
			{
				throw Exception("Audio device not found.", error_type_error); // Audio device not found
			}
		}
		else
		{
			this->deviceName = itDev->first;
		}


		return;
	}


	Alsa::~Alsa()
	{


		params.buffer.clear();

		// Close pcm handle
		//snd_pcm_drop(params.handle);
		snd_pcm_drain(params.handle);
		snd_pcm_close(params.handle);

		return;
	}


	std::vector<std::pair<std::string, std::string>> Alsa::GetDevices(const snd_pcm_stream_t type)
	{

		std::vector<std::pair<std::string, std::string>> devices;


		for(int card = 0; card >= 0; snd_card_next(&card))
		{

			snd_ctl_t* handle;

			const std::string name("hw:" + std::to_string(card));

			if(snd_ctl_open(&handle, name.data(), 0) < 0)
			{
				continue;
			}

			snd_ctl_card_info_t* cardInfo;
			snd_ctl_card_info_alloca(&cardInfo);
			if(snd_ctl_card_info(handle, cardInfo) < 0)
			{
				snd_ctl_close(handle);
				continue;
			}

			for(int dev = 0; dev >= 0; snd_ctl_pcm_next_device(handle, &dev))
			{
				snd_pcm_info_t* pcmInfo;
				snd_pcm_info_alloca(&pcmInfo);

				snd_pcm_info_set_device(pcmInfo, dev);
				snd_pcm_info_set_subdevice(pcmInfo, 0);
				snd_pcm_info_set_stream(pcmInfo, type);

				if(snd_ctl_pcm_info(handle, pcmInfo) < 0)
				{
					continue;
				}

				if(dev == 0)
				{
					const std::string deviceId("plughw:" + std::to_string(card) + "," + std::to_string(dev));
					const std::string deviceName(std::string(snd_ctl_card_info_get_name(cardInfo)) + " [hw:" + std::to_string(card) + "," + std::to_string(dev) + "]");
					devices.push_back(std::make_pair(deviceName, deviceId));
				}
			}

			snd_ctl_close(handle);
		}

		return devices;
	}


	void Alsa::Start()
	{

		auto sndErrorToException = [](auto code)
		{
			if(code != 0)
			{
				throw Exception(snd_strerror(code), error_type_error);
			}
		};

		sndErrorToException(snd_pcm_drop(params.handle));
		sndErrorToException(snd_pcm_prepare(params.handle));
		//sndErrorToException(snd_pcm_start(params.handle));

		if(params.capture)
		{
			rec = true;
			StartRecord();
		}
		else
		{
			play = true;
			StartPlayback();
		}

		return;
	}

	void Alsa::Stop()
	{

		if(params.capture)
		{
			rec = false;
			StopRecord();
		}
		else
		{
			play = false;
			StopPlayback();
		}

		return;
	}


	/// PRIVATE

	int Alsa::SetHwParams()
	{

		unsigned int realRate;
		snd_pcm_uframes_t size;
		int dir;

		snd_pcm_hw_params_any(params.handle, params.hwParams);
		snd_pcm_hw_params_set_rate_resample(params.handle, params.hwParams, 1);
		snd_pcm_hw_params_set_access(params.handle, params.hwParams, params.access);
		snd_pcm_hw_params_set_format(params.handle, params.hwParams, params.format);
		snd_pcm_hw_params_set_channels(params.handle, params.hwParams, params.nChannels);

		realRate = params.sampleRate;

		snd_pcm_hw_params_set_rate_near(params.handle, params.hwParams, &realRate, 0);

		//std::cout << "Real rate: " << realRate;

		snd_pcm_hw_params_set_buffer_time_near(params.handle, params.hwParams, &params.bufferTime, &dir);

		snd_pcm_hw_params_get_buffer_size(params.hwParams, &size);

		params.bufferSize = size;


		snd_pcm_hw_params_set_period_time_near(params.handle, params.hwParams, &params.periodTime, &dir);
		snd_pcm_hw_params_get_period_size(params.hwParams, &size, &dir);

		params.periodSize = size;
		params.buffer.resize(size);

		snd_pcm_hw_params(params.handle, params.hwParams);


		return 0;
	}

	int Alsa::SetSwParams()
	{

		snd_pcm_sw_params_current(params.handle, params.swParams);
		snd_pcm_sw_params_set_start_threshold(params.handle, params.swParams, (params.bufferSize / params.periodSize) * params.periodSize);
		snd_pcm_sw_params_set_avail_min(params.handle,params.swParams, params.periodSize);
		snd_pcm_sw_params(params.handle, params.swParams);

		return 0;
	}



	void Alsa::StartRecord()
	{

		recordThread = std::thread(&Alsa::Record, this);

		return;
	}

	void Alsa::StopRecord()
	{

		rec.store(false);

		recordThread.join();

		return;
	}

	void Alsa::Record()
	{

		return;
	}


	void Alsa::StartPlayback()
	{

		playThread = std::thread(&Alsa::Playback, this);

//		// Set maximum priority to the thread
//		sched_param sch_params;
//		sch_params.sched_priority = sched_get_priority_max(SCHED_FIFO);
//
//		pthread_setschedparam(playThread.native_handle(), SCHED_FIFO, &sch_params);

		Util::SetThreadPriority(playThread.native_handle(), 100);

		// Uncomment if debugging under Linux
		// pthread_setname_np(playThread.native_handle(), "Audio Thread\0");

		return;
	}

	void Alsa::StopPlayback()
	{

		play.store(false);
		playThread.join();

		return;
	}


	void Alsa::Playback()
	{

		int err = 0;

		while(play.load())
		{

			int frames = params.periodSize / params.nChannels;

			while(frames > 0)
			{

				//time_point<high_resolution_clock> t_start = high_resolution_clock::now();

				mixer->Mix(params.buffer);

				/*time_point<high_resolution_clock>  t_end = high_resolution_clock::now();

				auto d = duration<double, std::micro>(t_end-t_start).count();

				if(d > 20)
				{
				   std::cout << std::fixed << std::setprecision(2)
				   << "Wall clock time passed: "
				   << d
				   << " us" << std::endl;
				}
				*/

				err = snd_pcm_writei(params.handle, params.buffer.data(), frames);


				if (err == -EAGAIN)
				{
					continue;
				}

				if (err < 0)
				{
					XrunRecovery(err);
				}

				frames -= err;


			}

		}

		return;
	}

	void Alsa::XrunRecovery(int& err)
	{

		using namespace std::literals::chrono_literals;

		if (err == -EPIPE)
		{
			err = snd_pcm_prepare(params.handle);
		}
		else if (err == -ESTRPIPE)
		{

			while ((err = snd_pcm_resume(params.handle)) == -EAGAIN)
			{
				std::this_thread::sleep_for(1ms);
			}

			if (err < 0)
			{
				err = snd_pcm_prepare(params.handle);
			}
		}

		return;
	}

}

