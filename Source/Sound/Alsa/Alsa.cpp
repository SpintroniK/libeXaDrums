/*
 * Alsa.cpp
 *
 *  Created on: 11 Apr 2015
 *      Author: jeremy
 */

#include "Alsa.h"

using namespace std::chrono;

namespace Sound
{

	Alsa::Alsa(AlsaParams& parameters, std::shared_ptr<Mixer> const& mix, std::shared_ptr<SoundProcessor> const& soundProc)
	: params(parameters),
	  mixer(mix),
	  soundProc(soundProc),
	  play(false),
	  rec(false)

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
		else throw - 1;

		// Give parameters to mixer
		soundProc->SetAlsaParameters(&params);
		mix->SetAlsaParameters(&params);

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



	void Alsa::Start()
	{

		snd_pcm_drop(params.handle);
		snd_pcm_prepare(params.handle);
		snd_pcm_start(params.handle);

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
			play= false;
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

		params.buffer.assign(size, 0);


		snd_pcm_hw_params_set_period_time_near(params.handle, params.hwParams, &params.periodTime, &dir);
		snd_pcm_hw_params_get_period_size(params.hwParams, &size, &dir);

		params.periodSize = size;

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

		rec = false;

		while(!recordThread.joinable());

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

		return;
	}

	void Alsa::StopPlayback()
	{

		play = false;

		//while(!playThread.joinable());

		playThread.join();

		return;
	}


	void Alsa::Playback()
	{

		int err = 0;
		int index = 0, frames = 0;

		while(play)
		{

			frames 	= params.periodSize;

			while(frames > 0)
			{

				//time_point<high_resolution_clock> t_start = high_resolution_clock::now();

				mixer->Mix();


				err = snd_pcm_writei(params.handle, params.buffer.data(), frames);


				if (err == -EAGAIN)
					continue;

				if (err < 0)
					XrunRecovery(err);

				frames -= err;

				//time_point<high_resolution_clock>  t_end = high_resolution_clock::now();

			  /* std::cout << std::fixed << std::setprecision(2)
			   << "Wall clock time passed: "
			   << duration<double, std::milli>(t_end-t_start).count()
			   << " ms" << std::endl;*/

			}

			index 	+= err;

		}

		return;
	}

	int Alsa::XrunRecovery(int err)
	{

		if (err == -EPIPE)
		{
			err = snd_pcm_prepare(params.handle);
		}
		else if (err == -ESTRPIPE)
		{

			while ((err = snd_pcm_resume(params.handle)) == -EAGAIN)
				std::this_thread::sleep_for(milliseconds(1));

			if (err < 0)
				err = snd_pcm_prepare(params.handle);
		}

		return err;
	}

}
