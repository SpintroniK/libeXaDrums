/*
 * SoundSample.h
 *
 *  Created on: 27 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUND_H_
#define SOURCE_SOUND_SOUND_H_

#include <vector>
#include <memory>
#include <algorithm>

namespace Sound
{

	class Sound
	{

	public:

		Sound(int id, std::vector<short> soundData);
		virtual ~Sound();

		void SetVolume(float volume);
		void Seek(std::size_t index);
		void AddToIndex(int offset);

		bool HasMoreData(std::size_t length) const;

		int GetId() const { return this->id; }
		float GetVolume() const { return this->volume; }
		bool IsFinished() const { return idx >= data.size(); }
		std::size_t GetIndex() const { return idx; }
		const short* GetData() const { return data.data(); }



	private:

		int id;
		float volume;
		std::size_t idx;
		std::vector<short> data;

	};


	typedef std::shared_ptr<Sound> SoundPtr;

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUND_H_ */
