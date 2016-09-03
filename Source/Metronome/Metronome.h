/*
 * Metronome.h
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_METRONOME_H_
#define SOURCE_METRONOME_METRONOME_H_

#include "../Sound/Alsa/Alsa.h"

#include <vector>
#include <limits>

#include <cmath>

#define _USE_MATH_DEFINES

namespace DrumKit
{

	class Metronome
	{

	public:

		Metronome(Sound::AlsaParams alsaParams);
		virtual ~Metronome();

		void GenerateSine();

		void SetTempo(int tempo);

		std::vector<short> GetData() const { return data; }
		int GetTempo() const { return tempo; }


	private:

		Sound::AlsaParams alsaParameters;

		// Metronome parameters
		int tempo;
		int rhythm;
		int beatsPerMeasure;

		std::vector<short> data;

	};

} /* namespace DrumKit */

#endif /* SOURCE_METRONOME_METRONOME_H_ */
