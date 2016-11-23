/*
 * Curves.h
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_

#include <vector>


namespace DrumKit
{

	class Curves
	{

	public:

		static void Linear(std::vector<float>& curve);
		static void Exponential(std::vector<float>& curve);

		static const std::size_t numSamples = 2048;

	private:

		Curves(){};
		virtual ~Curves(){};

		static void Normalise(std::vector<float>& curve);

	};


}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_ */
