/*
 * Curves.cpp
 *
 *  Created on: 2 Jun 2015
 *      Author: jeremy
 */

#include "Curves.h"

namespace DrumKit
{

	void Curves::Linear(std::vector<float>& curve)
	{

		// Create a vector that contains values increasing from 0 to numSamples-1
		std::vector<float> linearVector(numSamples);
		std::iota(linearVector.begin(), linearVector.end(), 0.0f);

		// Normalise vector
		Normalise(linearVector);

		// Copy normalised vector into curve
		curve.swap(linearVector);

		return;
	}


	void Curves::Exponential(std::vector<float>& curve)
	{

		// Make sure curve is empty
		curve.clear();

		// Get normalised linear vector
		std::vector<float> normLin;
		Linear(normLin);

		// Create vector to contain the non-normalised exponential
		std::vector<float> expVector(normLin.size());

		// Create exponential function
		auto expFunc = [](float v) { return std::exp(v) - 1; };

		// Create non-normalised exponential vector
		std::transform(normLin.begin(), normLin.end(), expVector.begin(), expFunc);

		// Create normalised exponential vector
		Normalise(expVector);

		// Copy generated vector into the curve vector
		curve.swap(expVector);

		return;

	}


	// Private

	void Curves::Normalise(std::vector<float>& curve)
	{

		// Create empty vector to contain the normalised curve
		std::vector<float> normalisedCurve(curve.size());

		// Get maximum value of the vector
		float max = *std::max_element(curve.begin(), curve.end());

		// Create function for vector normalisation
		auto normFunc = [&max](float v){ return v/max; };

		// Normalise linear vector
		std::transform(curve.begin(), curve.end(), normalisedCurve.begin(), normFunc);

		// Copy normalised curve to the curve vector
		curve.swap(normalisedCurve);

		return;
	}

}

