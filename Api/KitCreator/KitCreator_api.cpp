/*
 * KitCreator.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: jeremy
 */

#include "KitCreator_api.h"

#include <algorithm>
#include <memory>


namespace eXaDrumsApi
{

	KitCreator::KitCreator(const char* dataLocation) : controller(*new DrumKit::KitCreator(dataLocation))
	{

		return;
	}

	KitCreator::~KitCreator()
	{

		// Delete controller
		delete &controller;

		return;
	}


	// Kit
	void KitCreator::CreateNewKit()
	{
		controller.CreateNewKit();
		return;
	}

	void KitCreator::CreateFromModel(const char* loc)
	{
		controller.CreateFromModel(std::string(loc));
		return;
	}

	int KitCreator::GetNumInstruments() const
	{
		return controller.GetNumInstruments();
	}

	void KitCreator::SetKitName(const char* name)
	{
		controller.SetKitName(std::string(name));
		return;
	}

	void KitCreator::SaveKit(const char* file) const
	{
		controller.SaveKit(std::string(file));
		return;
	}

	void KitCreator::SaveKit() const
	{
		controller.SaveKit();
		return;
	}

	// Instrument
	void KitCreator::CreateNewInstrument()
	{
		controller.CreateNewInstrument();
		return;
	}

	void KitCreator::RemoveInstrument(int i)
	{
		controller.RemoveInstrument(i);
		return;
	}

	void KitCreator::AddInstrumentToKit()
	{
		controller.AddInstrumentToKit();
		return;
	}

	void KitCreator::SetInstrumentName(const char* name)
	{
		controller.SetInstrumentName(std::string(name));
		return;
	}

	void KitCreator::SetInstrumentName(int id, const char* name)
	{
		controller.SetInstrumentName(id, std::string(name));
		return;
	}

	void KitCreator::SetInstrumentType(int id, const char* type)
	{
		controller.SetInstrumentType(id, std::string(type));
		return;
	}

	void KitCreator::SetInstrumentType(const char* type)
	{
		controller.SetInstrumentType(std::string(type));
		return;
	}

	void KitCreator::SetInstrumentVolume(const float volume)
	{
		controller.SetInstrumentVolume(volume);
		return;
	}

	void KitCreator::AddInstrumentSound(const char* file, const char* type)
	{
		controller.AddInstrumentSound(std::string(file), std::string(type));
		return;
	}

	void KitCreator::AddInstrumentTrigger(const int id, const char* location)
	{
		controller.AddInstrumentTrigger(id, std::string(location));
		return;
	}


	// Private Methods

	void KitCreator::SetInstrumentTriggersIdsAndLocs_(int id, int* ids, const char** locs, unsigned int size)
	{

		std::vector<int> trigsIds(ids, ids + size);
		std::vector<std::string> trigsLocs(locs, locs + size);

		std::vector<std::pair<int, std::string>> trigs;

		for(std::size_t i = 0; i < size; i++)
		{
			trigs.push_back({trigsIds[i], trigsLocs[i]});
		}

		controller.SetInstrumentTriggersIdsAndLocs(id, trigs);

		return;
	}

	void KitCreator::SetInstrumentSoundsTypesAndLocs_(int id, const char** types, const char** locs, unsigned int size)
	{

		std::vector<std::string> sndTypes(types, types + size);
		std::vector<std::string> sndLocs(locs, locs + size);

		std::vector<std::pair<std::string, std::string>> sounds;

		for(std::size_t i = 0; i < size; i++)
		{
			sounds.push_back({sndTypes[i], sndLocs[i]});
		}

		controller.SetInstrumentSoundsTypesAndLocs(id, sounds);

		return;
	}

	const char* KitCreator::GetInstrumentType_(int i)
	{

		this->instrumentType = controller.GetInstrumentType(i);

		return this->instrumentType.c_str();
	}

	void KitCreator::GetInstrumentTriggersIds_(int i, int* data, unsigned int& size) const
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentsTriggersIds(i).size();
			return;
		}

		std::vector<int> trigsIds = controller.GetInstrumentsTriggersIds(i);
		std::copy(trigsIds.cbegin(), trigsIds.cend(), data);
		size = trigsIds.size();

		return;
	}

	void KitCreator::GetTriggersIds_(int* data, unsigned int& size) const
	{

		if(data == nullptr)
		{
			size = controller.GetTriggersIds().size();
			return;
		}

		std::vector<int> trigsIds = controller.GetTriggersIds();
		std::copy(trigsIds.cbegin(), trigsIds.cend(), data);
		size = trigsIds.size();

		return;
	}

	void KitCreator::GetInstrumentTriggersLocations_(int i, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentTriggersLocations(i).size();
			return;
		}

		this->instrumentTriggersLocations.clear();
		this->instrumentTriggersLocations = controller.GetInstrumentTriggersLocations(i);

		unsigned int numElements = std::min<unsigned int>(size, instrumentTriggersLocations.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentTriggersLocations[i].c_str();
		}

		return;
	}

	void KitCreator::GetInstrumentSoundsTypes_(int i, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentSoundsTypes(i).size();
			return;
		}

		this->instrumentSoundsTypes.clear();
		this->instrumentSoundsTypes = controller.GetInstrumentSoundsTypes(i);

		unsigned int numElements = std::min<unsigned int>(size, instrumentSoundsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentSoundsTypes[i].c_str();
		}

		return;
	}
	void KitCreator::GetSoundTypes_(const char* instrumentType, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetSoundTypes(std::string(instrumentType)).size();
			return;
		}

		this->soundsTypes.clear();
		this->soundsTypes = controller.GetSoundTypes(std::string(instrumentType));

		unsigned int numElements = std::min<unsigned int>(size, soundsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = soundsTypes[i].c_str();
		}

		return;
	}


	void KitCreator::GetInstrumentSoundsLocs_(int i, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentSoundsLocs(i).size();
			return;
		}

		this->instrumentSoundsLocs.clear();
		this->instrumentSoundsLocs = controller.GetInstrumentSoundsLocs(i);

		unsigned int numElements = std::min<unsigned int>(size, instrumentSoundsLocs.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentSoundsLocs[i].c_str();
		}

		return;
	}

	void KitCreator::GetSoundFiles_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetSoundFiles().size();
			return;
		}

		this->soundsFiles.clear();
		this->soundsFiles = controller.GetSoundFiles();

		unsigned int numElements = std::min<unsigned int>(size, soundsFiles.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = soundsFiles[i].c_str();
		}

		return;
	}



	void KitCreator::GetInstrumentsTypes_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentsTypes().size();
			return;
		}

		this->instrumentsTypes.clear();
		this->instrumentsTypes = controller.GetInstrumentsTypes();

		unsigned int numElements = std::min<unsigned int>(size, instrumentsTypes.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentsTypes[i].c_str();
		}

		return;
	}

	void KitCreator::GetInstrumentsNames_(const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetInstrumentsNames().size();
			return;
		}

		this->instrumentsNames.clear();
		this->instrumentsNames = controller.GetInstrumentsNames();

		unsigned int numElements = std::min<unsigned int>(size, instrumentsNames.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = instrumentsNames[i].c_str();
		}

		return;
	}

	void KitCreator::GetTriggersLocations_(const char* instrumentType, const char** data, unsigned int& size)
	{

		if(data == nullptr)
		{
			size = controller.GetTriggersLocations(std::string(instrumentType)).size();
			return;
		}

		this->triggersLocations.clear();
		this->triggersLocations = controller.GetTriggersLocations(std::string(instrumentType));

		unsigned int numElements = std::min<unsigned int>(size, triggersLocations.size());

		for(unsigned int i = 0; i < numElements; i++)
		{
			data[i] = triggersLocations[i].c_str();
		}

		return;
	}



} /* namespace eXaDrumsApi */
