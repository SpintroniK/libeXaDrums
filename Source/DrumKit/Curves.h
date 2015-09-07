/*
 * Curves.h
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#ifndef SOURCE_DRUMKIT_CURVES_H_
#define SOURCE_DRUMKIT_CURVES_H_

#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>

namespace DrumKit
{

	class Curves
	{

	public:

		static void Linear(std::vector<float>& curve);
		static void Exponential(std::vector<float>& curve);

		static const size_t numSamples = 2048;

	private:

		Curves(){};
		virtual ~Curves(){};

		static void Normalise(std::vector<float>& curve);

	};


}


#endif /* SOURCE_DRUMKIT_CURVES_H_ */
