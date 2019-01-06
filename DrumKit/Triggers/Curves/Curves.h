/*
 * Curves.h
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#ifndef LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_
#define LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_

#include "../../../Util/Misc.h"
#include "../../../Util/Enums.h"
#include "CurveType.h"

#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>
#include <iostream>


namespace DrumKit
{

	template <typename T>
	using curve_t = std::vector<T>;

	class Curves
	{

	public:

		template <typename T>
		static curve_t<T> MakeCurve(CurveType t, size_t length)
		{

			curve_t<T> curve;

			switch(t)
			{
				case CurveType::Linear: Linear(curve, length); break;
				case CurveType::Exponential1: Exp(curve, length); break;
				case CurveType::Exponential2: Exp2(curve, length); break;
				case CurveType::Log1: Log(curve, length); break;
				case CurveType::Log2: Log2(curve, length); break;
				case CurveType::Loud1: Loud1(curve, length); break;
				case CurveType::Loud2: Loud2(curve, length); break;
				case CurveType::Spline: Sigmoid(curve, length); break;

				default: Linear(curve, length); break;
			}

			return curve;
		}

		template <typename T, typename U>
		static T Apply(const curve_t<T>& curve, U val)
		{
			const auto index = std::min<size_t>(val, curve.size()-1);

			return curve[index];
		}

		template <typename T>
		static void Linear(curve_t<T>& curve, std::size_t length)
		{

			// Create a vector that contains values increasing from 0 to numSamples-1
			std::vector<T> linearVector(length);
			std::iota(linearVector.begin(), linearVector.end(), 0);

			// Normalise vector
			Normalize(linearVector);

			// Copy normalised vector into curve
			curve.swap(linearVector);

			return;
		}

		template <typename T, typename F>
		static void GenerateNormalizedCurve(curve_t<T>& curve, std::size_t length, F&& func)
		{
			// Get normalised linear vector
			std::vector<T> normLin;
			Linear(normLin, length);

			// Create vector to contain the non-normalised cruve
			std::vector<T> curveVector(normLin.size());

			// Create non-normalised exponential vector
			std::transform(normLin.begin(), normLin.end(), curveVector.begin(), func);

			// Create normalised exponential vector
			Normalize(curveVector);

			// Copy generated vector into the curve vector
			curve.swap(curveVector);
		}

		template <typename T>
		static void Exp(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return std::expm1(x); });
			return;
		}

		template <typename T>
		static void Exp2(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return std::expm1(x) * std::expm1(x); });
			return;
		}


		template <typename T>
		static void Log(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return std::log2(1 + x); });
			return;
		}

		template <typename T>
		static void Log2(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return std::log2(1 + x) * std::log2(1 + x); });
			return;
		}

		template <typename T>
		static void Loud1(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return .25 + .75 * x; });
			return;
		}

		template <typename T>
		static void Loud2(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return .75 + .25 * x; });
			return;
		}

		template <typename T>
		static void Sigmoid(curve_t<T>& curve, std::size_t length)
		{
			GenerateNormalizedCurve(curve, length, [](auto x) { return 1. / ( 1. + std::exp(-12. * (x - .5))); });
			return;
		}



	private:

		Curves(){};
		virtual ~Curves(){};

		template <typename T>
		static void Normalize(std::vector<T>& curve)
		{

			// Create empty vector to contain the normalised curve
			std::vector<T> normalisedCurve(curve.size());

			// Get maximum value of the vector
			auto max = *std::max_element(curve.begin(), curve.end());

			// Normalise linear vector
			std::transform(curve.begin(), curve.end(), normalisedCurve.begin(), [&max](auto v) { return v/max; });

			// Copy normalised curve to the curve vector
			curve.swap(normalisedCurve);

			return;
		}

	};


}


#endif /* LIBEXADRUMS_SOURCE_DRUMKIT_CURVES_CURVES_H_ */
