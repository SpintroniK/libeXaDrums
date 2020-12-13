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
#include "../../Util/ErrorHandling.h"
#include "../../Sound/Util/WavUtil.h"

#include <iterator>
#include <chrono>
#include <set>
#include <map>
#include <valarray>
#include <iostream>

#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

using namespace Sound;
using namespace Util;

namespace DrumKit
{

	Recorder::Recorder(SoundBank* sndBankPtr, const AlsaParams& alsaParams) noexcept
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

	void Recorder::Stop()
	{
		isRecord.store(false, std::memory_order_release);
		recordThread.join();
	}

	void Recorder::Export(const std::string& fileName)
	{
		outputFile = fileName;
		ConvertFile(lastFile);
	}

	void Recorder::ExportPCM(const std::string& fileName)
	{
		outputFile = fileName;
		ConvertToPCM(lastFile);
	}

	// PRIVATE Methods

	void Recorder::DumpBufferToFile()
	{
		while(!buffer.empty())
		{
			TrigSound t  = buffer.front();
			buffer.pop();

			file << t.instrumentId << ',' << t.soundId << ',' << t.timeStamp << ',' << t.volume << '\n';
		}

		// Insert keyframe if the metronome is running
		auto lastClickTime = getLastClickTime();

		if(lastClickTime > 0)
		{
			file << -1 << ',' << -1 << ',' << lastClickTime << ',' << 0.5f << '\n';
		}

		file.flush();
	};

	void Recorder::Record()
	{

		using namespace Util;
		using namespace std::chrono_literals;
		using namespace std::chrono;
		using namespace std::this_thread;

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

		lastFile = fileName;
		//ConvertFile(fileName);

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
		using TrigSoundTuple = std::tuple<int, int, int64_t, float>;

		std::ifstream file{fileLoc};

		if(!file.good())
		{
			throw Exception("Could not load record file.", error_type_error);
		}

		// Read file line by line
		std::vector<std::string> lines{std::istream_iterator<Line>{file}, std::istream_iterator<Line>{}};

		XMLDocument doc;
		auto root = doc.NewElement("root");

		// We'll store all the sounds ids in that vector
		std::vector<int> soundsIds;
		soundsIds.reserve(lines.size());

		std::map<int, std::set<int>> instrumentsSounds;

		auto xmlSounds = CreateXmlElement(doc, "Sounds");
		root->InsertEndChild(xmlSounds);

		for(const auto& l : lines)
		{
			std::istringstream iss(l);
			std::vector<std::string> tokens{std::istream_iterator<Token<','>>{iss}, std::istream_iterator<Token<','>>{}};

			TrigSoundTuple tuple;
			VectorOfStrToTuple(tokens, tuple);

			TrigSound t;
			std::tie(t.instrumentId, t.soundId, t.timeStamp, t.volume) = tuple;

			soundsIds.push_back(t.soundId);
			instrumentsSounds[t.instrumentId].emplace(t.soundId);

			xmlSounds->InsertEndChild(CreateXmlElement(doc, "Sound", "", {{"Id", t.soundId}, {"TrigTime", t.timeStamp}, {"Volume", t.volume}}));
		}

		// Remove metronome from the instruments list
		instrumentsSounds.erase(-1);

		// Get all the unique sounds ids
		std::set<int> uniqueSoundsIds(soundsIds.begin(), soundsIds.end());

		// Remove the metronome from the set
		uniqueSoundsIds.erase(-1);

		// Create xml document
		// Header
		auto xmlHeader = CreateXmlElement(doc, "Header");
		{

			const auto fileTimeStamp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

			xmlHeader->InsertEndChild(CreateXmlElement(doc, "Date", TimeStampToStr(fileTimeStamp)));
			xmlHeader->InsertEndChild(CreateXmlElement(doc, "SampleRate", alsaParameters.sampleRate));
			xmlHeader->InsertEndChild(CreateXmlElement(doc, "NumberOfChannels", alsaParameters.nChannels));

			auto instrumentsXml = CreateXmlElement(doc, "Instruments");
			xmlHeader->InsertEndChild(instrumentsXml);

			for(const auto& instrumentSounds : instrumentsSounds)
			{
				instrumentsXml->InsertEndChild(CreateXmlElement(doc, "Instrument", "", {{"Id", instrumentSounds.first}, {"Sounds", JoinToStr(instrumentSounds.second, ", ")}}));
			}

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


			xmlHeader->InsertEndChild(xmlData);
		}


		doc.InsertFirstChild(root);
		if(outputFile.empty())
		{
			doc.SaveFile(std::string(directory + std::string("rec.xml")).data());
		}
		else
		{
			fs::path p{outputFile};
			if(p.extension() == ".xml")
			{
				doc.SaveFile(p.c_str());
			}
			else
			{
				doc.SaveFile((outputFile + ".xml").data());
			}
		}
	}

	void Recorder::ConvertToPCM(const std::string& inputFile)
	{

	}

} /* namespace DrumKit */


