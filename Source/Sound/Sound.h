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

namespace Sound
{

	class Sound
	{

	public:

		Sound(std::vector<short> soundData);
		Sound(std::vector<short> soundData, float volume);
		Sound(int id, std::vector<short> soundData);
		Sound(int id, std::vector<short> soundData, float volume);

		virtual ~Sound();

		void SetVolume(float volume);
		void Seek(std::size_t index);
		void AddToIndex(int offset);

		bool HasMoreData(std::size_t length) const;
		bool IsFinished() const { return idx >= data.size(); }

		void SetLoop(bool s) { loop = s; }

		int GetId() const { return this->id; }
		float GetVolume() const { return this->volume; }
		std::size_t GetIndex() const { return idx; }
		const short* GetData() const { return data.data(); }
		const std::vector<short> GetInternalData() const { return data; }
		inline const short GetValue(int i) const { return data[(i+idx)%length]; }
		bool IsLoop() const { return loop; }



	private:

		int id;
		float volume;
		bool loop;
		std::size_t idx;
		std::vector<short> data;
		int length;

	};


	typedef std::shared_ptr<Sound> SoundPtr;

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUND_H_ */
