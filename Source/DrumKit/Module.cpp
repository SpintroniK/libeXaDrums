/*
 * Drum.cpp
 *
 *  Created on: 6 May 2015
 *      Author: jeremy
 */

#include "Module.h"


namespace DrumKit
{

	Module::Module()
	: soundParameters(sndParams),
	  directory("./")
	{

		return;
	}

	Module::Module(std::string dir)
	: soundParameters(sndParams),
	  directory(dir)
	{

		return;
	}

	Module::~Module()
	{

		for(size_t i = 0; i < sndParams.size(); i++)
			delete[] sndParams[i].data;

		sndParams.clear();

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

			size_t drumId = kit.drum.size();

			bool newSound = GetDrumParams(drumName, kit.drum);

			std::string drumFileName = kit.drum.front().soundFile;
			std::string fileSound = directory + "Kits/" + kit.kitFolder + "/" + drumFileName;

			// Sound id must match drumId (index in the kit.drum vector)
			AddSound(fileSound, drumId);

			drumId++;

			if(!newSound) 
				getSound = false;

		}


		//xmlFreeDoc(doc);
		xmlFree(doc);
		//xmlCleanupParser();
	    //xmlMemoryDump();

		return;
	}


	/// PRIVATE

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

		short* soundData = new short[fileSize];

		soundFile.seekg(0, std::ios::beg);

		int i = 0;
		while(soundFile.read((char*)&soundData[i], sizeof(short))) i++;

		SoundParams sndParameters;

		sndParameters.length 	= fileSize*sizeof(char)/sizeof(short);
		sndParameters.data 		= soundData;
		sndParameters.id 		= soundId;

		// Add sound to lib
		sndParams.push_back(sndParameters);

		// Close file
		soundFile.close();

		return;
	}


	bool Module::GetDrumParams(xmlNode* drumName, std::vector<Drum>& drums)
	{

		Drum drum;

		drum.id 			= drums.size();

		drum.drumName 		= std::string((char*) drumName->children->content);

		xmlNode* soundFile 	= drumName->next->next;
		drum.soundFile 		= std::string((char*) soundFile->children->content);

		xmlNode* threshold 	= soundFile->next->next;
		drum.threshold 		= (short) std::atoi((char*) threshold->children->content);

		xmlNode* scanTime	= threshold->next->next;
		drum.scanTime 		= (int) std::atoi((char*) scanTime->children->content);

		xmlNode* maskTime 	= scanTime->next->next;
		drum.maskTime 		= (int) std::atoi((char*) maskTime->children->content);

		xmlNode* curve 		= maskTime->next->next;
		std::string curveName = std::string((char*) curve->children->content);

		GetDrumCurve(curveName, drum.curve);

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

