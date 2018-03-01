/*
 * Recorder.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: jeremy
 */

#include "Recorder.h"

#include "../../Util/Parsing.h"
#include "../../Util/Misc.h"
#include "../../Util/Xml.h"
#include "../../Util/Time.h"
#include "../../Util/Crypt.h"

#include <iterator>
#include <chrono>
#include <set>
#include <iostream>

using namespace Sound;

namespace DrumKit
{

	Recorder::Recorder(SoundBank* sndBankPtr, const AlsaParams& alsaParams)
	: isRecord{false}, soundBankPtr{sndBankPtr}, alsaParameters{alsaParams}
	{

	}

	Recorder::~Recorder()
	{
		isRecord.store(false, std::memory_order_relaxed);

		if(recordThread.joinable())
		{
			recordThread.join();
		}
	}

	void Recorder::Start()
	{
		isRecord.store(true, std::memory_order_release);
		recordThread = std::thread(&Recorder::Record, this);
	}

	void Recorder::StopAndExport()
	{
		isRecord.store(false, std::memory_order_release);
		recordThread.join();
	}

	// PRIVATE Methods

	void Recorder::DumpBufferToFile()
	{
		while(!buffer.empty())
		{
			int soundId;
			float volume;
			int64_t time;
			std::tie(soundId, time, volume) = buffer.front();
			buffer.pop();

			file << soundId << ',' << time << ',' << volume << '\n';
		}

		// Insert keyframe if the metronome is running
		auto lastClickTime = getLastClickTime();

		if(lastClickTime > 0)
		{
			file << -1 << ',' << lastClickTime << ',' << 0.5f << '\n';
		}

		file.flush();
	};

	void Recorder::Record()
	{

		using namespace Util;
		using namespace std::chrono_literals;
		using namespace std::chrono;
		using namespace std::this_thread;

		using TrigSound = std::tuple<int, int64_t, float>;

		// Create new file
		const auto fileTimeStamp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		const std::string fileName = directory + std::to_string(fileTimeStamp) + ".csv";

		file.open(fileName);

		while(isRecord.load(std::memory_order_acquire))
		{

			TrigSound trigSound;

			while(recordQueue.Pop(trigSound))
			{
				buffer.emplace(std::move(trigSound));
			}

			// Write data to file
			if(buffer.size() >= recordQueue.Capacity() / 8)
			{
				DumpBufferToFile();
			}

			// Wait before we try to get more sounds
			if(isRecord.load(std::memory_order_relaxed))
			{
				sleep_for(500ms);
			}

		}

		DumpBufferToFile();

		file.close();

		ConvertFile(fileName);

	}

	/**
	 * Converts the temporary csv file to an xml file.
	 * @param fileLoc File location.
	 */
	void Recorder::ConvertFile(const std::string& fileLoc)
	{
		using namespace Util;
		using namespace tinyxml2;
		using namespace std::chrono;
		using TrigSound = std::tuple<int, int64_t, float>;

		std::ifstream file{fileLoc};

		// Read file line by line
		std::vector<std::string> lines{std::istream_iterator<Line>{file}, std::istream_iterator<Line>{}};

		XMLDocument doc;
		auto root = doc.NewElement("root");

		// We'll store all the sounds ids in that vector
		std::vector<int> soundsIds;
		soundsIds.reserve(lines.size());

		for(const auto& l : lines)
		{
			std::istringstream iss(l);
			std::vector<std::string> tokens{std::istream_iterator<Token<','>>{iss}, std::istream_iterator<Token<','>>{}};

			TrigSound tuple;
			VectorOfStrToTuple(tokens, tuple);

			int soundId;
			float volume;
			int64_t time;
			std::tie(soundId, time, volume) = tuple;

			soundsIds.push_back(soundId);

			root->InsertEndChild(CreateXmlElement(doc, "Sound", "", {{"Id", soundId}, {"TrigTime", time}, {"Volume", volume}}));
		}

		// Get all the unique sounds ids
		std::set<int> uniqueSoundsIds(soundsIds.begin(), soundsIds.end());

		// Remove the metronome from the set
		uniqueSoundsIds.erase(-1);

		// Create xml document
		// Header
		{

			const auto fileTimeStamp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

			auto xmlHeader = CreateXmlElement(doc, "Header");

			xmlHeader->InsertEndChild(CreateXmlElement(doc, "Date", TimeStampToStr(fileTimeStamp)));
			xmlHeader->InsertEndChild(CreateXmlElement(doc, "SampleRate", alsaParameters.sampleRate));
			xmlHeader->InsertEndChild(CreateXmlElement(doc, "NumberOfChannels", alsaParameters.nChannels));

			root->InsertFirstChild(xmlHeader);
		}

		// Data
		{
			auto xmlData = CreateXmlElement(doc, "Data");

			for(const auto& soundId : uniqueSoundsIds)
			{
				const auto& sound = soundBankPtr->GetSound(soundId);
				const auto& soundData = sound.GetInternalData();

				xmlData->InsertEndChild(CreateXmlElement(doc, "Sound", Base64Encode(soundData), {{"Id", soundId}}));
			}


			root->InsertFirstChild(xmlData);
		}


		doc.InsertFirstChild(root);
		doc.SaveFile(std::string(directory + std::string("rec.xml")).data());
	}

} /* namespace DrumKit */


