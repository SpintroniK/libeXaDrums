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
			this->AddSound(soundLocation, soundData, soundDuration);

			//!! Force sensor type to the one defined by the module (temporary)
			instrumentParameters.sensorType = this->sensorType;


			//!! Force curve (temporary)
			std::vector<float> drumCurve;
			GetDrumCurve("linear", drumCurve);

			instrumentParameters.curve = drumCurve;

			// Create instrument for drum module
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

	void Module::AddSound(std::string filename, std::vector<short>& data, unsigned int& duration)
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

/*
	bool Module::GetDrumParams(xmlNode* drumName, std::vector<std::shared_ptr<Instrument>>& instruments)
	{

		InstrumentParameters instruParams;

		instruParams.id = instruments.size();
		instruParams.sensorType = this->sensorType;

		//drum.SetId(drums.size());


		std::string instrumentName = std::string((char*) drumName->children->content);

		instruParams.instrumentName = instrumentName;

		xmlNode* sensorId 	= drumName->next->next;
		instruParams.sensorId =  (int) std::atoi((char*) sensorId->children->content);

		xmlNode* soundFile 	= sensorId->next->next;
		instruParams.soundFile = std::string((char*) soundFile->children->content);

		xmlNode* threshold 	= soundFile->next->next;
		instruParams.threshold = (short) std::atoi((char*) threshold->children->content);

		xmlNode* scanTime	= threshold->next->next;
		instruParams.scanTime = (int) std::atoi((char*) scanTime->children->content);

		xmlNode* maskTime 	= scanTime->next->next;
		instruParams.maskTime = (int) std::atoi((char*) maskTime->children->content);

		xmlNode* curve 		= maskTime->next->next;
		std::string curveName = std::string((char*) curve->children->content);

		std::vector<float> drumCurve;
		GetDrumCurve(curveName, drumCurve);

		instruParams.curve = drumCurve;

		std::shared_ptr<Instrument> instrument = std::shared_ptr<Instrument>(new Drum(instruParams));

		instrument->CreateTrigger();

		instruments.push_back(instrument);

		if(curve->parent->next->next)
			*drumName = *curve->parent->next->next->children->next;
		else
			return false;

		return true;
	}
	*/

	Sound::DrumCurve Module::GetCurveType(std::string curveName)
	{
		// Create map
		std::map<std::string, Sound::DrumCurve> dic;

		// Add definitions to dic
		dic["exponential"] = Sound::DrumCurve::exponential;
		dic["linear"] = Sound::DrumCurve::linear;

		std::map< std::string, Sound::DrumCurve>::iterator i = dic.find(curveName);

		if(i != dic.end())
			return i->second;
		else
			return Sound::DrumCurve::linear; // Default value

	}

	void Module::GetDrumCurve(std::string curveName, std::vector<float>& curve)
	{

		Sound::DrumCurve drumCurve = GetCurveType(curveName);

		switch(drumCurve)
		{

		case Sound::DrumCurve::exponential:
				Sound::Curves::Exponential(curve);
			break;

		default:
				Sound::Curves::Linear(curve);
			break;
		}

		return;
	}

}

