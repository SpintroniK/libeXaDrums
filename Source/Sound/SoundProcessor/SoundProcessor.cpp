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
		this->sounds.push_back(Sound(id, soundData));

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

		std::function<void(Sound)> update = [this](Sound sound)
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

	void SoundProcessor::ReadSoundChunk(int soundId, std::vector<short>& chunk)
	{

		sounds[soundId].ReadChunk(chunk);

		return;
	}




} /* namespace Sound */
