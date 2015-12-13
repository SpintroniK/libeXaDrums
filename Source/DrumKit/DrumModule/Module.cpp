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
	: soundParameters(),
	  sensorType(sensorType),
	  directory(dir),
	  isPlay(false),
	  soundProc(soundProc)
	{

		return;
	}

	Module::~Module()
	{

		sndParams.clear();

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

		const char* fileName 	= file.c_str();

		//xmlInitParser();

		xmlDoc* doc 			= xmlReadFile(fileName, NULL, 0);
		xmlNode* rootElement 	= xmlDocGetRootElement(doc);

		xmlNode* node 			= rootElement->children;

		xmlNode* kitName 		= node->next;
		this->drumKitName		= std::string((char*) kitName->children->content);

		xmlNode* kitFolder 		= kitName->next->next;
		this->drumKitFolder		= std::string((char*) kitFolder->children->content);

		xmlNode* kitParams 		= kitFolder->next->next;

		std::string instrumentType = std::string((char*)kitParams->properties->children->content);

		xmlNode* drumName 		= kitParams->children->next;

		bool getSound = true;

		while(getSound)
		{

			size_t drumId = instruments.size();

			bool newSound = GetDrumParams(drumName, instruments);

			std::string drumFileName(instruments[drumId]->GetSoundFile());
			std::string fileSound = directory + "SoundBank/" + drumFileName;

			// Sound id must match drumId (index in the kit.drum vector)
			AddSound(fileSound, drumId);

			drumId++;

			if(!newSound) 
				getSound = false;

		}

		this->soundParameters = sndParams;

		//xmlFreeDoc(doc);
		xmlFree(doc);
		//xmlCleanupParser();
	    //xmlMemoryDump();

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

	void Module::AddSound(std::string filename, size_t soundId)
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


		SoundParams sndParameters;
		sndParameters.data.clear();
		sndParameters.data.resize(fileSize);

		int i = 0;
		while(soundFile.read((char*)&sndParameters.data[i], sizeof(short))) i++;


		sndParameters.length 	= fileSize*sizeof(char)/sizeof(short);
		sndParameters.id 		= soundId;

		//sndParameters.data.clear();

		//std::copy(&soundData[0], &soundData[sndParameters.length], std::back_inserter(sndParameters.data));

		// Add sound to lib
		sndParams.push_back(sndParameters);

		// Close file
		soundFile.close();

		return;
	}


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

