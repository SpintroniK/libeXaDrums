/*
 * Metronome.h
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_METRONOME_METRONOME_H_
#define SOURCE_METRONOME_METRONOME_H_

#include "../Sound/Alsa/AlsaParams.h"

#include "ClickTypes.h"
#include "MetronomeParameters.h"


#include <vector>
#include <string>



namespace DrumKit
{

	class Metronome
	{

	public:

		explicit Metronome(Sound::AlsaParams alsaParams) noexcept;
		Metronome(Sound::AlsaParams alsaParams, MetronomeParameters params) noexcept;
		virtual ~Metronome();

		void GenerateClick() noexcept;

		void SetParameters(const MetronomeParameters& params) { parameters = params; }
		void SetClickType(const ClickType& type) { parameters.clickType = type; }
		void SetRhythm(int rhythm) noexcept { parameters.rhythm = rhythm; }
		void SetBpmeas(int bpmeas) noexcept { parameters.beatsPerMeasure = bpmeas; }
		void SetTempo(int tempo);

		MetronomeParameters GetParameters() const { return parameters; }
		ClickType GetClickType() const noexcept { return parameters.clickType; }
		int GetTempo() const noexcept { return parameters.tempo; }
		int GetRhythm() const noexcept { return parameters.rhythm; }
		int GetBpmeas() const noexcept { return parameters.beatsPerMeasure; }

		std::vector<int> GetRhythmList() const { return rhythmList; }
		std::vector<int> GetBpmeasList() const { return bpmeasList; }
		std::vector<short> GetData() const noexcept { return data; }


		static void LoadConfig(const std::string& filePath, MetronomeParameters& params);
		static void SaveConfig(const std::string& filePath, const MetronomeParameters& params);


	private:


		void GenerateSine();
		void GenerateSquare();

		int GetNumSamples() const;
		int GetBeatsRate() const;

		Sound::AlsaParams alsaParameters;

		// Metronome parameters
		MetronomeParameters parameters;

		std::vector<int> bpmeasList;
		std::vector<int> rhythmList;

		std::vector<short> data;

	};

} /* namespace DrumKit */

#endif /* SOURCE_METRONOME_METRONOME_H_ */
