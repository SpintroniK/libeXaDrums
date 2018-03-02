/*
 * Enums.h
 *
 *  Created on: 29 Sep 2016
 *      Author: jeremy
 */

#ifndef SOURCE_UTIL_ENUMS_H_
#define SOURCE_UTIL_ENUMS_H_

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace Util
{

	/**
	 * Helper function to make conversion to enums easier.
	 * @param is Input stream.
	 * @param x Enum type to convert the input stream to.
	 * @return
	 */
	template <typename T>
	inline std::istream& StreamToEnum(std::istream& is, T& x)
	{

		std::string s;
		is >> s;

		for(const auto& l : T())
		{
			std::ostringstream os;
			os << l;

			if(os.str() == s)
			{
				x = l;
			}
		}

		return is;
	}


	class Enums
	{

	public:

		template<typename T>
		static std::string ToString(const T& e)
		{

			std::stringstream ss;

			for (const auto& c : T())
			{
				if(c == e)
				{
					ss << e;
					return ss.str();
				}
			}

			//XXX Temporary (can't throw because of unfinished stuff).
			ss << T::First;
			return ss.str();
		}

		template<typename T>
		static T ToElement(const std::string& s)
		{

			for (const auto& c : T())
			{
				std::stringstream ss;
				ss << c;

				if(ss.str() == s)
				{
					return c;
				}
			}

			//XXX Temporary (can't throw because of unfinished stuff).
			return T::First;
		}



		template<typename T>
		static std::vector<T> GetEnumVector()
		{

			std::vector<T> v;

			for (const auto& c : T())
			{
				v.push_back(c);
			}

			return v;
		}


	private:

		Enums() = delete;
		virtual ~Enums() = delete;

	};

}

#endif /* SOURCE_UTIL_ENUMS_H_ */
