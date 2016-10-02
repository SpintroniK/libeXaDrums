/*
 * Metronome.cpp
 *
 *  Created on: 28 Aug 2016
 *      Author: jeremy
 */

#include "Metronome.h"

using namespace Sound;

namespace DrumKit
{

	Metronome::Metronome(AlsaParams alsaParams) : alsaParameters(alsaParams),
	clickType(ClickType::First), tempo(120), rhythm(2), beatsPerMeasure(4)
 	{

		return;
	}

	Metronome::~Metronome()
	{

		return;
	}


	void Metronome::GenerateClick()
	{

		switch (this->clickType)
		{
			case ClickType::Sine: 	GenerateSine();		break;
			case ClickType::Square: GenerateSquare();	break;

			default: break;
		}


		return;
	}

	// Private Methods

	int Metronome::GetNumSamples() const
	{
		// Calculate number of samples to generate the measure
		float beatsPerSecond = rhythm * float(tempo) / 60.0f;
		float measureTime = beatsPerMeasure / beatsPerSecond;
		int numSamples = alsaParameters.sampleRate * measureTime;

		return numSamples;
	}

	int Metronome::GetBeatsRate() const
	{
		// Get number of samples between each click
		float beatsPerSecond = rhythm * float(tempo) / 60.0f;
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

	        	if(n % beatsPerMeasure == 0)
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

	        	if(n % beatsPerMeasure == 0)
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


	void Metronome::SetTempo(int t)
	{

		tempo = t;

		if(tempo >= 250) tempo = 250;
		if(tempo <= 40) tempo = 40;

		return;
	}

} /* namespace DrumKit */
