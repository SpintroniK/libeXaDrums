/*
 * SoundProcessor.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: jeremy
 */


#include "SoundProcessor.h"

namespace Sound
{

	SoundProcessor::SoundProcessor() : alsaParams(), sounds()
	{

		return;
	}

	SoundProcessor::~SoundProcessor()
	{

		sounds.clear();

		return;
	}


	void SoundProcessor::SetAlsaParameters(AlsaParams* alsaParameters)
	{

		this->alsaParams = alsaParameters;

		return;
	}


	void SoundProcessor::AddSound(int& id, std::vector<short> soundData)
	{

		id = this->sounds.size();

		// Add sound to the list of sounds
		this->sounds.push_back(SoundSample(id, soundData));

		// Add sound id to the play list
		//this->playList.insert(std::pair<int, bool>(id, false));

		return;
	}

	const std::vector<int>& SoundProcessor::GetPlayList() const
	{
		return playList;
	}

	void SoundProcessor::UpdatePlayList()
	{

		//std::lock_guard<std::mutex> lock(soundProcMutex);

		std::function<void(SoundSample)> update = [this](SoundSample sound)
		{

			if(sound.IsFinished())
			{
				//FIXME That thing is wrong!!!
				//this->playList[sound.GetId()] = false;
				//playList.erase(std::remove_if(playList.begin(), playList.end(),
				//		[&sound](int soundId) { return (soundId == sound.GetId()); }), playList.end());

				sound.SeekBeg();
			}

		};


		std::for_each(sounds.begin(), sounds.end(), update);

		return;
	}


	void SoundProcessor::PlaySound(int soundId)
	{

		//std::lock_guard<std::mutex> lock(soundProcMutex);

		bool isPlaying = std::find(playList.begin(), playList.end(), soundId) != playList.end();

		if(isPlaying)
		{
			sounds[soundId].SeekBeg();
		}
		else
		{
			playList.push_back(soundId);
		}

		return;
	}

	short SoundProcessor::ReadSoundData(int soundId)
	{
		return sounds[soundId].ReadData();
	}

/*
	void SoundProcessor::AddSound(int id, float volume)
	{

		std::lock_guard<std::mutex> lock(soundProcMutex);



		//Test if the sound has already been added to the mixer
		std::vector<SampleInfo>::iterator iter =	std::find_if(soundList.begin(), soundList.end(),
				[id](const SampleInfo& sound) { return sound.id == id; });

		// Find sound's position in the vector
		size_t i = std::distance(soundList.begin(), iter);

		if(i != soundList.size())
		{
			// The sound is already in the sound list, so we need to rewind it
			soundList[i].index = 0;
			// We also have to make sure to play the sound with the new volume
			soundList[i].volume = volume;

		}
		else
		{

			SampleInfo sample;

			sample.id = id;
			sample.index = 0;
			sample.volume = volume;

			soundList.push_back(sample);
		}

		return;
	}

	void SoundProcessor::GetSamples(std::vector<std::vector<short>>& samples)
	{


		samples.clear();

		for(size_t j = 0; j < soundList.size(); j++)
		{

			std::vector<short> buffer(alsaParams->periodSize);
			int instrumentId = soundList[j].id;

			for(int i = 0; i < alsaParams->periodSize; i++)
			{
				buffer[i] = soundList[j].volume * sounds[instrumentId][soundList[j].index + i];
			}

			soundList[j].index += alsaParams->periodSize;

			this->sampleList.push_back(buffer);
		}

		samples.swap(this->sampleList);

		return;

	}

	void SoundProcessor::DumpSamples()
	{

		// Delete the sounds that finished playing
		std::function<bool(SampleInfo)> f = [this](SampleInfo sample)
		{
			return (sample.index >= durations[sample.id]);
		};
		soundList.erase(std::remove_if(soundList.begin(), soundList.end(), f), soundList.end());

		//sampleList.clear();

		return;
	}
*/



} /* namespace Sound */
