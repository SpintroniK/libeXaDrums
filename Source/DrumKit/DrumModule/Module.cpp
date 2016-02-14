/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"


namespace DrumKit
{

	Module::Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::SoundProcessor> const& soundProc)
	: sensorType(sensorType),
	  directory(dir),
	  isPlay(false),
	  soundProc(soundProc)
	{

		return;
	}

	Module::~Module()
	{


		return;
	}


	void Module::Start()
	{

		isPlay = true;

		playThread = std::thread(&Module::Run, this);

		return;
	}


	void Module::Stop()
	{

		isPlay = false;

		while(!playThread.joinable());

		playThread.join();

		return;
	}

	void Module::GetDirectory(std::string& dir) const
	{

		dir = this->directory;

		return;
	}

	void Module::LoadKit(std::string file)
	{


		// Prepare instruments vector to be populated
		this->instruments.clear();

		// Load drum kit parameters
		KitParameters::LoadKit(file, this->kitParameters);


		std::function<void(InstrumentParameters)> fInst = [this](InstrumentParameters instrumentParameters)
		{

			// Sound file location
			std::string soundLocation = this->directory + "SoundBank/" + instrumentParameters.soundFile;

			std::vector<short> soundData;
			unsigned int soundDuration;

			// Add sound data to soundData vector
			this->LoadSound(soundLocation, soundData, soundDuration);

			//XXX Force sensor type to the one defined by the module (temporary)
			instrumentParameters.sensorType = this->sensorType;

			//XXX Force curve to linear (temporary)
			instrumentParameters.curveType = Sound::CurveType::linear;

			//XXX Create instrument for drum module (Drum only for now)
			std::shared_ptr<Instrument> instrument = std::shared_ptr<Instrument>(new Drum(instrumentParameters));

			// Set sound data for this instrument
			instrument->SetSoundData(soundData, soundDuration);

			// Create trigger for the instrument
			instrument->CreateTrigger();

			this->soundProc->SetInstrumentSounds(instrument->GetSoundData(), instrument->GetSoundDuration());

			// Add instrument to drum module
			instruments.push_back(instrument);

		};

		std::for_each(this->kitParameters.instrumentParameters.begin(),
				this->kitParameters.instrumentParameters.end(), fInst);



		return;
	}


	/// PRIVATE


	void Module::Run()
	{

		std::function<void(std::shared_ptr<Instrument>)> f = [this] (std::shared_ptr<Instrument> instrument)
		{

			float strength = 0;
			bool isTrig = instrument->Trig(strength);

			if(isTrig)
			{
				// !TODO convert strength to volume (SoundProcessor)
				this->soundProc->AddSound(instrument->GetId(), strength);
			}

		};

		while(isPlay)
		{
			std::for_each(instruments.begin(), instruments.end(), f);
		}

		return;
	}

	void Module::LoadSound(std::string filename, std::vector<short>& data, unsigned int& duration)
	{


		// Get file location
		std::string fileLocation(filename);

		// Open file
		std::ifstream soundFile(fileLocation);

		// Check file validity
		if(!soundFile.good())
			throw - 1;

		soundFile.seekg (0, std::ios::end);

		// Get file size in bytes
		int fileSize = soundFile.tellg();

		//short* soundData = new short[fileSize];

		soundFile.seekg(0, std::ios::beg);


		data.clear();
		data.resize(fileSize);

		int i = 0;
		while(soundFile.read((char*)&data[i], sizeof(short))) i++;

		duration = fileSize*sizeof(char)/sizeof(short);


		// Close file
		soundFile.close();

		return;
	}

}

