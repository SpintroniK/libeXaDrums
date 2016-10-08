/*
 * Metronome.h
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_METRONOME_H_
#define SOURCE_METRONOME_METRONOME_H_

#include "../Sound/Alsa/Alsa.h"
#include "../Util/Enums.h"

#include "ClickTypes.h"
#include "MetronomeParameters.h"

#include <tinyxml2.h>

#include <vector>
#include <limits>
#include <string>

#include <cmath>

#define _USE_MATH_DEFINES

namespace DrumKit
{

	class Metronome
	{

	public:

		Metronome(AlsaParams alsaParams);
		Metronome(AlsaParams alsaParams, MetronomeParameters params);
		virtual ~Metronome();

		void GenerateClick();

		void SetParameters(const MetronomeParameters& params) { parameters = params; }
		void SetClickType(const ClickType& type) { parameters.clickType = type; };
		void SetTempo(int tempo);

		MetronomeParameters GetParameters() const { return parameters; }
		ClickType GetClickType() const { return parameters.clickType; }
		int GetTempo() const { return parameters.tempo; }
		std::vector<int> GetRhythmList() const { return rhythmList; }
		std::vector<int> GetBpmeasList() const { return bpmeasList; }
		std::vector<short> GetData() const { return data; }


		static void LoadConfig(const std::string& filePath, MetronomeParameters& params);
		static void SaveConfig(const std::string& filePath, const MetronomeParameters& params);


	private:


		void GenerateSine();
		void GenerateSquare();

		int GetNumSamples() const;
		int GetBeatsRate() const;

		AlsaParams alsaParameters;

		// Metronome parameters
		MetronomeParameters parameters;

		std::vector<int> bpmeasList;
		std::vector<int> rhythmList;

		std::vector<short> data;

	};

} /* namespace DrumKit */

#endif /* SOURCE_METRONOME_METRONOME_H_ */
