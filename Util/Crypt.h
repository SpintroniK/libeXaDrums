/*
 * Crypt.h
 *
 *  Created on: 26 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_CRYPT_H_
#define SOURCE_UTIL_CRYPT_H_

#include <array>
#include <vector>
#include <string>
#include <algorithm>

namespace Util
{

	static constexpr char Base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	static constexpr std::array<int, 256> Base64Indices = {{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
	   56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
		7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
		0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	   41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 }};

	static std::string Base64Encode(const std::vector<uint8_t>& str)
	{
		const auto len = str.size();
		size_t d = len % 3;

		std::string str64(4 * (int(d > 0) + len / 3), '=');

		for(size_t i = 0, j = 0; i < len - d; i += 3)
		{
			int32_t n = int32_t(str[i]) << 16 | int32_t(str[i + 1]) << 8 | str[i + 2];
			str64[j++] = Base64Chars[n >> 18];
			str64[j++] = Base64Chars[n >> 12 & 0x3F];
			str64[j++] = Base64Chars[n >> 6 & 0x3F];
			str64[j++] = Base64Chars[n & 0x3F];
		}

		if(d-- > 0)	// Padding
		{
			int32_t n = d ? int32_t(str[len - 2]) << 8 | str[len - 1] : str[len - 1];
			str64[str64.size() - 2] = d ? Base64Chars[(n & 0xF) << 2] : '=';
			str64[str64.size() - 3] = d ? Base64Chars[n >> 4 & 0x03F] : Base64Chars[(n & 3) << 4];
			str64[str64.size() - 4] = d ? Base64Chars[n >> 10] : Base64Chars[n >> 2];
		}

		return str64;
	}

	template <typename T>
	static std::string Base64Encode(const std::vector<T>& input)
	{
	    std::vector<uint8_t> str;
	    str.reserve(sizeof(T) * input.size());

	    std::copy_n(reinterpret_cast<const char*>(input.data()), sizeof(T) * input.size(), std::back_inserter(str));

	    return Base64Encode(str);
	}

	/*static std::string Base64Decode(const std::string& str64)
	{
		const auto len = str64.size();
		const auto pad = len > 0 && (len % 4 || str64[len - 1] == '=');
		const size_t length = ((len + 3) / 4 - pad) * 4;

		std::string str(length / 4 * 3 + pad, '\0');

		for(size_t i = 0, j = 0; i < length; i += 4)
		{
			int32_t n = Base64Indices[str64[i]] << 18 | Base64Indices[str64[i + 1]] << 12 | Base64Indices[str64[i + 2]] << 6 | Base64Indices[str64[i + 3]];
			str[j++] = n >> 16;
			str[j++] = n >> 8 & 0xFF;
			str[j++] = n & 0xFF;
		}

		if(pad != 0)
		{
			int32_t n = Base64Indices[str64[length]] << 18 | Base64Indices[str64[length + 1]] << 12;
			str.back() = n >> 16;

			if (len > length + 2 && str64[length + 2] != '=')
			{
				n |= Base64Indices[str64[length + 2]] << 6;
				str.push_back(n >> 8 & 0xFF);
			}
		}

		return str;
	}
	*/
}

#endif /* SOURCE_UTIL_CRYPT_H_ */
