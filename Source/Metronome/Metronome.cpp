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
	tempo(120), rhythm(1), beatsPerMeasure(4)
 	{

		return;
	}

	Metronome::~Metronome()
	{

		return;
	}


	void Metronome::GenerateSine()
	{

		data.clear();

		// Calculate number of samples to generate the measure
		float beatsPerSecond = rhythm * float(tempo) / 60.0f;
		float measureTime = beatsPerMeasure / beatsPerSecond;
		const int numSamples = alsaParameters.sampleRate * measureTime;

		//
		//float nPeriods = float(numSamples) / float(alsaParameters.periodSize);
		//float offset = nPeriods - int(nPeriods);
		//int correction = offset * std::floor(alsaParameters.periodSize);

		data.resize(numSamples);//std::floor(nPeriods)*alsaParameters.periodSize);

		// Get number of samples between each click
		float beatsFreq = 1/beatsPerSecond;
		int beatsRate = std::floor(alsaParameters.sampleRate*beatsFreq);

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
