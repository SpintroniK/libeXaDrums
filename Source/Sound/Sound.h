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
#include <atomic>

namespace Sound
{

	class Sound
	{

	public:

		Sound();
		Sound(Sound& s);
		Sound(Sound&& s);
		Sound(std::vector<short> soundData);
		Sound(std::vector<short> soundData, float volume);
		Sound(int id, std::vector<short> soundData);
		Sound(int id, std::vector<short> soundData, float vol);

		virtual ~Sound();

		friend void swap(Sound& first, Sound& second) noexcept
		{
			using std::swap;

			swap(first.id, second.id);
			swap(first.loop, second.loop);
			swap(first.data, second.data);
			swap(first.length, second.length);

			// "swap" atomics
			second.volume.store(first.volume.exchange(second.volume.load()));
			second.idx.store(first.idx.exchange(second.idx.load()));

			return;
		}

		Sound& operator=(Sound s) noexcept
		{
			swap(*this, s);
			return *this;
		}



		void SetVolume(float volume);
		void Seek(std::size_t index);
		void AddToIndex(int offset);

		bool HasMoreData(std::size_t length) const;
		bool IsFinished() const { return idx.load() >= (int)data.size(); }

		void SetLoop(bool s) { loop = s; }

		int GetId() const { return this->id; }
		inline float GetVolume() const noexcept { return volume.load(); }
		int GetIndex() const noexcept { return idx.load(); }
		const short* GetData() const { return data.data(); }
		const std::vector<short> GetInternalData() const { return data; }
		inline const short GetValue(int i) const noexcept { return data[(i + idx) % length]; }
		bool IsLoop() const { return loop; }



	private:

		int id;
		bool loop;
		std::atomic<int> idx;
		std::vector<short> data;
		int length;
		std::atomic<float> volume;

	};


	typedef std::shared_ptr<Sound> SoundPtr;

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUND_H_ */
