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

	Alsa::Alsa(AlsaParams& parameters, Mixer& mix)
	: params(parameters),
	  mixer(mix),
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

		return;
	}


	Alsa::~Alsa()
	{


		delete[] params.buffer;

		// Close pcm handle
		//snd_pcm_drop(params.handle);
		snd_pcm_drain(params.handle);
		snd_pcm_close(params.handle);

		return;
	}

	void Alsa::ReadXmlConfig(AlsaParams& params, const std::string fileLocation)
	{

		const char* fileName 	= fileLocation.c_str();

		//xmlInitParser();

		xmlDoc* doc 			= xmlReadFile(fileName, NULL, 0);
		xmlNode* rootElement 	= xmlDocGetRootElement(doc);

		xmlNode* node 			= rootElement->children;

		xmlNode* device 		= node->next;
		params.device 			= std::string((char*) device->children->content);

		xmlNode* capture 		= device->next->next;
		params.capture 			= (bool) std::atoi((char*) capture->children->content);

		xmlNode* format 		= capture->next->next;
		GetSndFormat((char*) format->children->content, params.format);

		xmlNode* sampleRate 	= format->next->next;
		params.sampleRate		= (unsigned int) std::atoi((char*) sampleRate->children->content);

		xmlNode* nChannels 		= sampleRate->next->next;
		params.nChannels		= (unsigned int) std::atoi((char*) nChannels->children->content);

		xmlNode* bufferTime 	= nChannels->next->next;
		params.bufferTime 		= (unsigned int) std::atoi((char*) bufferTime->children->content);

		xmlNode* periodTime		= bufferTime->next->next;
		params.periodTime 		= (unsigned int) std::atoi((char*) periodTime->children->content);

		xmlNode* access 		= periodTime->next->next;
		GetAccessType((char*) access->children->content, params.access);


		xmlFree(doc);
		//xmlCleanupParser();
	    //xmlMemoryDump();


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

		params.buffer = new short[size];


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

		while(!playThread.joinable());

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

				mixer.Mix();


				err = snd_pcm_writei(params.handle, params.buffer, frames);

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


	void Alsa::GetSndFormat(const char* fName, snd_pcm_format_t& format)
	{

		std::string formatName(fName);
		std::map<std::string, snd_pcm_format_t> dic;

		// Add definitions to dic
		dic["SND_PCM_FORMAT_S16_LE"] = SND_PCM_FORMAT_S16_LE;

		std::map< std::string, snd_pcm_format_t>::iterator i = dic.find(formatName);

		if(i != dic.end())
			format = i->second;
		else
			format = SND_PCM_FORMAT_S8; // Default value

		return;
	}

	void Alsa::GetAccessType(const char* aName, _snd_pcm_access& access)
	{

		std::string accessName(aName);
		std::map<std::string, _snd_pcm_access> dic;

		// Add definitions to dic
		dic["SND_PCM_ACCESS_RW_INTERLEAVED"] = SND_PCM_ACCESS_RW_INTERLEAVED;
		dic["SND_PCM_ACCESS_MMAP_INTERLEAVED"] = SND_PCM_ACCESS_MMAP_INTERLEAVED;

		std::map< std::string, _snd_pcm_access>::iterator i = dic.find(accessName);

		if(i != dic.end())
			access = i->second;
		else
			access = SND_PCM_ACCESS_RW_INTERLEAVED; // Default value

		return;

	}


}
