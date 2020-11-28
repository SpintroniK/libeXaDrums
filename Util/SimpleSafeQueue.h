/*
 * SimpleSafeQueue.h
 *
 *  Created on: 20 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_SIMPLESAFEQUEUE_H_
#define SOURCE_UTIL_SIMPLESAFEQUEUE_H_

#include <atomic>
#include <array>
#include <cstddef>

namespace Util
{

	/**
	 * A thread-safe Single Producer Single Consumer queue.
	 * Its size is fixed, it's a circular buffer.
	 * Default size = 32.
	 */
	template<typename T, size_t Length = 64>
	class SimpleSafeQueue
	{

	public:

		/**
		 * @brief Pushes new value to the queue, and returns true if successful.
		 * @param value
		 * @return true if the queue isn't full, false otherwise.
		 */
		bool Push(const T& value)
		{

			const auto oldWriterIndex = writerIndex.load(std::memory_order_relaxed);
			const auto newWriterIndex = GetNextIndex(oldWriterIndex);

			// Is the queue full?
			if(newWriterIndex == readerIndex.load(std::memory_order_acquire))
			{
				return false;
			}

			buffer[oldWriterIndex] = value;

			writerIndex.store(newWriterIndex, std::memory_order_release);

			return true;
		}

		/**
		 * @brief Pops an element from the queue, and returns true if successful.
		 * @param value
		 * @return true if the queue isn't empty, false otherwise.
		 */
		bool Pop(T& value)
		{
			const auto oldWriterIndex = writerIndex.load(std::memory_order_acquire);
			const auto oldReaderIndex = readerIndex.load(std::memory_order_relaxed);


			// Is the queue empty?
			if(oldWriterIndex == oldReaderIndex)
			{
				return false;
			}

			value = std::move(buffer[oldReaderIndex]);

			readerIndex.store(GetNextIndex(oldReaderIndex), std::memory_order_release);

			return true;
		}

		/**
		 * @brief Returns the number of elements that the queue can hold.
		 * @return
		 */
		constexpr size_t Capacity() const { return Length; }

	private:

		static constexpr size_t GetNextIndex(size_t pos) noexcept
		{
			return (++pos == bufferSize)? 0 : pos;
		}

		static constexpr size_t bufferSize = Length + 1;

		std::array<T, bufferSize> buffer;
		std::atomic<size_t> writerIndex{0};
		std::atomic<size_t> readerIndex{0};

	};

}


#endif /* SOURCE_UTIL_SIMPLESAFEQUEUE_H_ */
