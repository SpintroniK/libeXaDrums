/*
 * Metronome.h
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_METRONOME_H_
#define SOURCE_METRONOME_METRONOME_H_

#include "../Sound/Alsa/Alsa.h"

#include "ClickTypes.h"

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

		void GenerateClick();

		void SetClickType(const ClickType& type);
		void SetTempo(int tempo);

		ClickType GetClickType() const { return clickType; }
		int GetTempo() const { return tempo; }
		std::vector<short> GetData() const { return data; }


	private:

		void GenerateSine();
		void GenerateSquare();

		int GetNumSamples() const;
		int GetBeatsRate() const;

		Sound::AlsaParams alsaParameters;

		// Metronome parameters
		ClickType clickType;
		int tempo;
		int rhythm;
		int beatsPerMeasure;

		std::vector<short> data;

	};

} /* namespace DrumKit */

#endif /* SOURCE_METRONOME_METRONOME_H_ */
