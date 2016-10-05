/*
 * Metronome.cpp
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#include "Metronome.h"

using namespace Sound;
using namespace tinyxml2;

namespace DrumKit
{

	Metronome::Metronome(AlsaParams alsaParams) : Metronome(alsaParams, MetronomeParameters())
	{


		return;
	}

	Metronome::Metronome(AlsaParams alsaParams, MetronomeParameters params) : alsaParameters(alsaParams), parameters(params)
 	{

		bpmeasList = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
		rhythmList = std::vector<int>{1, 2, 4};


		return;
	}



	Metronome::~Metronome()
	{

		return;
	}


	void Metronome::GenerateClick()
	{

		switch (this->parameters.clickType)
		{
			case ClickType::Sine: 	GenerateSine();		break;
			case ClickType::Square: GenerateSquare();	break;

			default: break;
		}


		return;
	}



	void Metronome::SetTempo(int t)
	{

		parameters.tempo = t;



		if(parameters.tempo >= 250) parameters.tempo = 250;
		if(parameters.tempo <= 40) parameters.tempo = 40;

		return;
	}


	void Metronome::LoadConfig(const std::string& filePath, MetronomeParameters& params)
	{



		return;
	}

	void Metronome::SaveConfig(const std::string& filePath, const MetronomeParameters& params)
	{

		// Create document
		XMLDocument doc;

		// Add root element
		XMLElement* root = doc.NewElement("Metronome");
		doc.InsertFirstChild(root);

		// Create elements
		XMLElement* tempo = doc.NewElement("Tempo");
		XMLElement* rhythm = doc.NewElement("Rhythm");
		XMLElement* beatsPerMeasure = doc.NewElement("BeatsPerMeasure");
		XMLElement* clickType = doc.NewElement("ClickType");

		// Add values and elements to document
		tempo->SetText(params.tempo);
		rhythm->SetText(params.rhythm);
		beatsPerMeasure->SetText(params.beatsPerMeasure);
		clickType->SetText(Util::Enums::ClickTypeToString(params.clickType).c_str());

		// Add elements to document
		root->InsertEndChild(tempo);
		root->InsertEndChild(rhythm);
		root->InsertEndChild(beatsPerMeasure);
		root->InsertEndChild(clickType);

		// Save file
		doc.SaveFile(filePath.c_str());

		return;
	}


	// Private Methods

	int Metronome::GetNumSamples() const
	{
		// Calculate number of samples to generate the measure
		float beatsPerSecond = parameters.rhythm * float(parameters.tempo) / 60.0f;
		float measureTime = parameters.beatsPerMeasure / beatsPerSecond;
		int numSamples = alsaParameters.sampleRate * measureTime;

		return numSamples;
	}

	int Metronome::GetBeatsRate() const
	{
		// Get number of samples between each click
		float beatsPerSecond = parameters.rhythm * float(parameters.tempo) / 60.0f;
		float beatsFreq = 1/beatsPerSecond;
		int beatsRate = std::floor(alsaParameters.sampleRate*beatsFreq);

		return beatsRate;
	}

	void Metronome::GenerateSquare()
	{

		const int numSamples = GetNumSamples();

		data.clear();
		data.resize(numSamples);

		// Get number of samples between each click
		const int beatsRate = GetBeatsRate();

		// Sinusoid parameters
		float fSineHz = 880.0f;
		float radiansPerSample = fSineHz * 2*M_PI / alsaParameters.sampleRate;
		float clickDuration = 10.0f/1000.0f;
		std::size_t clickSamples = std::floor(alsaParameters.sampleRate*clickDuration);

		int n = 0;
		int mul = 1;
		std::size_t click;
		double phase = 0;
		short amplitude = std::numeric_limits<short>::max();

		for(std::size_t i = 0; i < data.size(); i++)
		{

			click = n * beatsRate;// + correction;

	        if(i > click && i < click + clickSamples)
	        {

	        	if(n % parameters.beatsPerMeasure == 0)
	        	{
	        		mul = 2;
	        	}
	        	else
	        	{
	        		mul = 1;
	        	}

	        	phase  		+= mul*radiansPerSample;
	        	data[i] 	 = (short)(float(amplitude) * (std::sin(phase) > 0));

	        }
	        else  // No click, so signal is zero
	        {

	        	data[i] = 0;
	        	phase = 0;

	        	if(i == click + clickSamples)
	        	{
	        		n++;
	        	}
	        }

		}

		return;
	}

	void Metronome::GenerateSine()
	{


		const int numSamples = GetNumSamples();

		data.clear();
		data.resize(numSamples);

		// Get number of samples between each click
		const int beatsRate = GetBeatsRate();

		// Sinusoid parameters
		float fSineHz = 880.0f;
		float radiansPerSample = fSineHz * 2*M_PI / alsaParameters.sampleRate;
		float clickDuration = 10.0f/1000.0f;
		std::size_t clickSamples = std::floor(alsaParameters.sampleRate*clickDuration);

		int n = 0;
		int mul = 1;
		std::size_t click;
		double phase = 0;
		short amplitude = std::numeric_limits<short>::max();

		for(std::size_t i = 0; i < data.size(); i++)
		{

			click = n * beatsRate;// + correction;

	        if(i > click && i < click + clickSamples)
	        {

	        	if(n % parameters.beatsPerMeasure == 0)
	        	{
	        		mul = 2;
	        	}
	        	else
	        	{
	        		mul = 1;
	        	}

	        	phase  		+= mul*radiansPerSample;
	        	data[i] 	 = (short)(float(amplitude) * std::sin(phase));

	        }
	        else  // No click, so signal is zero
	        {

	        	data[i] = 0;
	        	phase = 0;

	        	if(i == click + clickSamples)
	        	{
	        		n++;
	        	}
	        }

		}

		return;
	}


} /* namespace DrumKit */
