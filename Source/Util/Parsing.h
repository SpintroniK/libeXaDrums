/*
 * Parsing.h
 *
 *  Created on: 25 Feb 2018
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_PARSING_H_
#define SOURCE_UTIL_PARSING_H_

#include <istream>

namespace Util
{

	template <char delim>
	class Token
	{

	public:

		friend std::istream& operator>>(std::istream& is, Token& t)
		{
			std::getline(is, t.data, delim);
			return is;
		}

		operator std::string() const { return data; }

		static constexpr char delimiter = delim;

	private:

		std::string data;
	};

	using Line = Token<'\n'>;


}

#endif /* SOURCE_UTIL_PARSING_H_ */
