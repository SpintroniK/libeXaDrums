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
#include <exception>


namespace Sound
{


	template <typename T>
	inline T bytes_to_word(const std::vector<uint8_t>& bytes)
	{
		return std::accumulate(bytes.rbegin(), bytes.rend(), T{0}, [](T a, T b) { return a << 8 | b; });
	}

	template <typename T>
	inline std::vector<T> subvector(const std::vector<T>& vec, size_t i, size_t j)
	{
		return std::vector<T>(vec.begin() + i, vec.begin() + j);
	}

	inline std::string bytes_to_string(const std::vector<uint8_t>& bytes, size_t start = 0, size_t stop = 0)
	{
		if(stop == 0)
		{
			stop  = bytes.size();
		}
		return std::string(bytes.begin() + start, bytes.begin() + stop);
	}

	class wav_header
	{

	public:

		explicit wav_header(const std::vector<uint8_t>& header_data)
		: chunk_id(bytes_to_string(header_data, 0, 4)),
		  format(bytes_to_string(header_data, 8, 12)),
		  subchunk1_id(bytes_to_string(header_data, 12, 16)),
		  subchunk2_id(bytes_to_string(header_data, 36, 40))
		{

			chunk_size 		= bytes_to_word<uint32_t>(subvector(header_data, 4, 8));
			subchunk1_size 	= bytes_to_word<uint32_t>(subvector(header_data, 16, 20));
			audio_format 	= bytes_to_word<uint16_t>(subvector(header_data, 20, 22));
			num_channels 	= bytes_to_word<uint16_t>(subvector(header_data, 22, 24));
			sample_rate 	= bytes_to_word<uint32_t>(subvector(header_data, 24, 28));
			byte_rate		= bytes_to_word<uint32_t>(subvector(header_data, 28, 32));
			block_align		= bytes_to_word<uint16_t>(subvector(header_data, 32, 34));
			bits_per_sample	= bytes_to_word<uint16_t>(subvector(header_data, 34, 36));
			subchunk2_size 	= bytes_to_word<uint32_t>(subvector(header_data, 40, 44));

		}

		inline uint32_t get_subchunk2_size() const noexcept { return subchunk2_size; }

		~wav_header() = default;

	private:

		wav_header() = delete;

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
