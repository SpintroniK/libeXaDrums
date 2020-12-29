/*
 * WavUtil.h
 *
 *  Created on: 12 Nov 2017
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_UTIL_WAVUTIL_H_
#define SOURCE_SOUND_UTIL_WAVUTIL_H_

#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iostream>

namespace Sound
{


	template <typename T>
	inline T BytesToWord(const std::vector<uint8_t>& bytes)
	{
		return std::accumulate(bytes.rbegin(), bytes.rend(), T{0}, [](T a, T b) { return a << 8 | b; });
	}

	template <typename T>
	inline std::vector<T> SubVector(const std::vector<T>& vec, size_t i, size_t j)
	{
		return std::vector<T>(vec.begin() + i, vec.begin() + j);
	}

	inline std::string BytesToString(const std::vector<uint8_t>& bytes, size_t start = 0, size_t stop = 0)
	{
		if(stop == 0)
		{
			stop  = bytes.size();
		}
		return std::string(bytes.begin() + start, bytes.begin() + stop);
	}

	template <typename T>
	inline std::enable_if_t<!std::is_arithmetic<T>::value, void> CopyBytesToVector(const T& bytes, std::vector<uint8_t>& vec, size_t offset)
	{
		std::copy(std::begin(bytes), std::end(bytes), vec.begin() + offset);
	}

	template <typename T>
	inline std::enable_if_t<std::is_arithmetic<T>::value, void> CopyBytesToVector(const T& bytes, std::vector<uint8_t>& vec, size_t offset)
	{
		auto ptr = reinterpret_cast<const uint8_t*>(&bytes);
		CopyBytesToVector(std::vector<uint8_t>(ptr, ptr + sizeof(T)), vec, offset);
	}

	class WavHeader
	{

	public:

		explicit WavHeader(const std::vector<uint8_t>& header_data)
		: chunk_id(BytesToString(header_data, 0, 4)),
		  format(BytesToString(header_data, 8, 12)),
		  subchunk1_id(BytesToString(header_data, 12, 16)),
		  subchunk2_id(BytesToString(header_data, 36, 40))
		{

			chunk_size		= BytesToWord<uint32_t>(SubVector(header_data, 4, 8));
			subchunk1_size 	= BytesToWord<uint32_t>(SubVector(header_data, 16, 20));
			audio_format 	= BytesToWord<uint16_t>(SubVector(header_data, 20, 22));
			num_channels 	= BytesToWord<uint16_t>(SubVector(header_data, 22, 24));
			sample_rate 	= BytesToWord<uint32_t>(SubVector(header_data, 24, 28));
			byte_rate		= BytesToWord<uint32_t>(SubVector(header_data, 28, 32));
			block_align		= BytesToWord<uint16_t>(SubVector(header_data, 32, 34));
			bits_per_sample	= BytesToWord<uint16_t>(SubVector(header_data, 34, 36));
			subchunk2_size 	= BytesToWord<uint32_t>(SubVector(header_data, 40, 44));

		}

		WavHeader() : 	chunk_id("RIFF"), chunk_size(0), format("WAVE"), subchunk1_id("fmt "), subchunk1_size(16),
						audio_format(1), num_channels(2), sample_rate(48000), byte_rate(192000), block_align(4), bits_per_sample(16),
						subchunk2_id("data"), subchunk2_size(0)
		{}

		void SetDataLength(size_t length) noexcept
		{
			subchunk2_size = length;
			chunk_size = subchunk2_size + 36;
		}

		void SetSampleRate(uint32_t sampleRate)
		{
			sample_rate = sampleRate;
			byte_rate = num_channels * sample_rate * (bits_per_sample / 8);
		}

		std::vector<uint8_t> ToBytes() const
		{

			std::vector<uint8_t> headerData(44);

			CopyBytesToVector(chunk_id, 		headerData, 0);
			CopyBytesToVector(chunk_size, 		headerData, 4);
			CopyBytesToVector(format,			headerData, 8);

			CopyBytesToVector(subchunk1_id, 	headerData, 12);
			CopyBytesToVector(subchunk1_size, 	headerData, 16);
			CopyBytesToVector(audio_format, 	headerData, 20);
			CopyBytesToVector(num_channels, 	headerData, 22);
			CopyBytesToVector(sample_rate, 		headerData, 24);
			CopyBytesToVector(byte_rate, 		headerData, 28);
			CopyBytesToVector(block_align, 		headerData, 32);
			CopyBytesToVector(bits_per_sample, 	headerData, 34);
			CopyBytesToVector(subchunk2_id, 	headerData, 36);
			CopyBytesToVector(subchunk2_size, 	headerData, 40);


			return headerData;
		}

		inline uint32_t get_subchunk2_size() const noexcept { return subchunk2_size; }

		~WavHeader() = default;

	private:

		std::string chunk_id;
		uint32_t chunk_size;
		std::string format;

		std::string subchunk1_id;
		uint32_t subchunk1_size;
		uint16_t audio_format;
		uint16_t num_channels;
		uint32_t sample_rate;
		uint32_t byte_rate;
		uint16_t block_align;
		uint16_t bits_per_sample;

		std::string subchunk2_id;
		uint32_t subchunk2_size;

	};

//	static std::vector<short> load_wav_from_disk(const std::string& file_location)
//	{
//
//		// Open file
//		std::ifstream file(file_location);
//
//		// Check file validity
//		if(!file.good())
//		{
//			throw std::runtime_error("Couldn't load file.");
//		}
//
//		// HEADER
//		std::vector<uint8_t> header_data(44);
//		file.read((char*)header_data.data(), header_data.size());
//		wav_header header(header_data);
//
//		// DATA
//		auto data_size{header.get_subchunk2_size()};
//
//		uint32_t data_size_short = data_size / sizeof(short);
//		std::vector<short> data(data_size_short);
//
//		file.read((char*)data.data(), data_size);
//
//		return data;
//	}



}

#endif /* SOURCE_SOUND_UTIL_WAVUTIL_H_ */
