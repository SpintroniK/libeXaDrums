/*
 * Metronome.cpp
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#include "Metronome.h"

#include "../Util/Enums.h"
#include "../Util/ErrorHandling.h"

#include <tinyxml2.h>

#include <limits>

#include <cmath>

#define _USE_MATH_DEFINES

using namespace Sound;
using namespace tinyxml2;
using namespace Util;

namespace DrumKit
{

	Metronome::Metronome(AlsaParams alsaParams) noexcept : Metronome(alsaParams, MetronomeParameters())
	{


		return;
	}

	Metronome::Metronome(AlsaParams alsaParams, MetronomeParameters params) noexcept : alsaParameters(alsaParams), parameters(params)
 	{

		bpmeasList = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8};
		rhythmList = std::vector<int>{1, 2, 4};


		return;
	}



	Metronome::~Metronome()
	{

		return;
	}


	void Metronome::GenerateClick() noexcept
	{

		switch (this->parameters.clickType)
		{
			case ClickType::Sine: 	GenerateSine();		break;
			case ClickType::Square: GenerateSquare();	break;

			default: GenerateSine(); break;
		}


		return;
	}



	void Metronome::SetTempo(int t)
	{

		parameters.tempo = std::min<int>(std::max<int>(t, 40), 250);

		return;
	}


	void Metronome::LoadConfig(const std::string& filePath, MetronomeParameters& params)
	{

		XMLDocument doc;

		if(doc.LoadFile(filePath.c_str()) != XML_SUCCESS)
		{
			throw Exception("Could not load metronome configuration.", error_type_error);
		}

		// Get elements
		XMLElement* root = doc.RootElement();
		XMLElement* tempo = root->FirstChildElement("Tempo");
		XMLElement* rhythm = root->FirstChildElement("Rhythm");
		XMLElement* beatsPerMeasure = root->FirstChildElement("BeatsPerMeasure");
		XMLElement* clickType = root->FirstChildElement("ClickType");

		// Get values
		params.tempo = std::atoi(tempo->GetText());
		params.rhythm = std::atoi(rhythm->GetText());
		params.beatsPerMeasure = std::atoi(beatsPerMeasure->GetText());
		params.clickType = Enums::ToElement<ClickType>(clickType->GetText());

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
		clickType->SetText(Enums::ToString(params.clickType).c_str());

		// Add elements to document
		root->InsertEndChild(tempo);
		root->InsertEndChild(rhythm);
		root->InsertEndChild(beatsPerMeasure);
		root->InsertEndChild(clickType);

		// Save file
		auto err = doc.SaveFile(filePath.c_str());

		if(err != XML_SUCCESS)
		{
			throw Exception("Could not save metronome configuration.", error_type_error);
		}

		return;
	}


	// Private Methods

	int Metronome::GetNumSamples() const
	{
		// Calculate number of samples to generate the measure
		float beatsPerSecond = parameters.rhythm * float(parameters.tempo) / 60.0f;
		float measureTime = parameters.beatsPerMeasure / beatsPerSecond;
		int numSamples = alsaParameters.nChannels * alsaParameters.sampleRate * measureTime;

		return numSamples;
	}

	int Metronome::GetBeatsRate() const
	{
		// Get number of samples between each click
		float beatsPerSecond =  parameters.rhythm * float(parameters.tempo) / 60.0f;
		float beatsFreq = alsaParameters.nChannels/beatsPerSecond;
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
		float radiansPerSample = fSineHz * 2*M_PI / alsaParameters.sampleRate / alsaParameters.nChannels;
		float clickDuration = alsaParameters.nChannels * 10.0f/1000.0f;
		std::size_t clickSamples = std::floor(alsaParameters.sampleRate*clickDuration);

		int n = 0;
		int mul = 1;
		double phase = 0;
		short amplitude = std::numeric_limits<short>::max();

		for(std::size_t i = 0; i < data.size(); i++)
		{
			std::size_t click = n * beatsRate;// + correction;

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
		float radiansPerSample = fSineHz * 2*M_PI / alsaParameters.sampleRate / alsaParameters.nChannels;
		float clickDuration = alsaParameters.nChannels * 10.0f/1000.0f;
		std::size_t clickSamples = std::floor(alsaParameters.sampleRate*clickDuration);

		int n = 0;
		int mul = 1;
		double phase = 0;
		short amplitude = std::numeric_limits<short>::max();

		for(std::size_t i = 0; i < data.size(); i++)
		{

			std::size_t click = n * beatsRate;// + correction;

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
