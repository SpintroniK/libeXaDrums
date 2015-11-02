/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"


namespace DrumKit
{

	Module::Module(std::string dir, IO::SensorType sensorType, std::shared_ptr<Sound::Mixer> const& mixer)
	: sensorType(sensorType),
	  soundParameters(),
	  directory(dir),
	  isPlay(false),
	  mixer(mixer)
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

	void Module::LoadKit(std::string file, Kit& kit)
	{

		const char* fileName 	= file.c_str();

		//xmlInitParser();

		xmlDoc* doc 			= xmlReadFile(fileName, NULL, 0);
		xmlNode* rootElement 	= xmlDocGetRootElement(doc);

		xmlNode* node 			= rootElement->children;

		xmlNode* kitName 		= node->next;
		kit.kitName				= std::string((char*) kitName->children->content);

		xmlNode* kitFolder 		= kitName->next->next;
		kit.kitFolder 			= std::string((char*) kitFolder->children->content);

		xmlNode* kitParams 		= kitFolder->next->next;
		xmlNode* drumName 		= kitParams->children->next;

		bool getSound = true;

		while(getSound)
		{

			size_t drumId = drums.size();

			bool newSound = GetDrumParams(drumName, drums);

			std::string drumFileName(drums[drumId].GetSoundFile());
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

		std::function<void(Drum)> f = [this] (Drum drum)
		{

			float volume = 0;
			bool isTrig = drum.Trig(volume);

			if(isTrig)
			{
				this->mixer->AddToMixer(drum.GetId(), volume);
			}

		};

		while(isPlay)
		{
			std::for_each(drums.cbegin(), drums.cend(), f);
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


	bool Module::GetDrumParams(xmlNode* drumName, std::vector<Drum>& drums)
	{

		//drum.SetId(drums.size());

		//std::string drumName = std::string((char*) drumName->children->content);

		xmlNode* sensorId 	= drumName->next->next;
		int drumSensorId =  (int) std::atoi((char*) sensorId->children->content);


		Drum drum(drums.size(), drumSensorId, sensorType);

		xmlNode* soundFile 	= sensorId->next->next;
		drum.SetSoundFile(std::string((char*) soundFile->children->content));

		xmlNode* threshold 	= soundFile->next->next;
		drum.SetThreshold((short) std::atoi((char*) threshold->children->content));

		xmlNode* scanTime	= threshold->next->next;
		drum.SetScanTime((int) std::atoi((char*) scanTime->children->content));

		xmlNode* maskTime 	= scanTime->next->next;
		drum.SetMaskTime((int) std::atoi((char*) maskTime->children->content));

		xmlNode* curve 		= maskTime->next->next;
		std::string curveName = std::string((char*) curve->children->content);

		std::vector<float> drumCurve;
		GetDrumCurve(curveName, drumCurve);

		drum.SetCurve(drumCurve);

		drum.CreateTrigger();

		drums.push_back(drum);

		if(curve->parent->next->next)
			*drumName = *curve->parent->next->next->children->next;
		else
			return false;

		return true;
	}

	DrumCurve Module::GetCurveType(std::string curveName)
	{
		// Create map
		std::map<std::string, DrumCurve> dic;

		// Add definitions to dic
		dic["exponential"] = DrumCurve::exponential;
		dic["linear"] = DrumCurve::linear;

		std::map< std::string, DrumCurve>::iterator i = dic.find(curveName);

		if(i != dic.end())
			return i->second;
		else
			return DrumCurve::linear; // Default value

	}

	void Module::GetDrumCurve(std::string curveName, std::vector<float>& curve)
	{

		DrumCurve drumCurve = GetCurveType(curveName);

		switch(drumCurve)
		{

		case DrumCurve::exponential:
				Curves::Exponential(curve);
			break;

		default:
				Curves::Linear(curve);
			break;
		}

		return;
	}

}

