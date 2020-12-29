/*
 * eXaDrums.hpp
 *
 *  Created on: 18 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_API_EXADRUMS_HPP_
#define SOURCE_API_EXADRUMS_HPP_


#include "eXaDrums.h"


namespace eXaDrumsApi
{

	inline void eXaDrums::Start()
	{
		Util::ErrorToException([&] { return this->Start_(); });
	}

	inline void eXaDrums::Stop()
	{
		Util::ErrorToException([&] { return this->Stop_(); });
	}

	inline void eXaDrums::EnableRecording(bool enable)
	{
		Util::ErrorToException([&] { return this->EnableRecording_(enable); });
	}

	inline void eXaDrums::SelectKit(std::size_t id)
	{
		Util::ErrorToException([&] { return this->SelectKit_(id); });
	}

	inline void eXaDrums::SaveKitConfig(std::size_t id) const
	{
		Util::ErrorToException([&] { return this->SaveKitConfig_(id); });
	}

	inline void eXaDrums::DeleteKit(std::size_t id)
	{
		Util::ErrorToException([&] { return this->DeleteKit_(id); });
	}

	inline std::string eXaDrums::GetDataLocation() const noexcept
	{
		return std::string(this->GetDataLocation_());
	}

	inline std::string eXaDrums::GetVersion() noexcept
	{
		return std::string(eXaDrums::GetVersion_());
	}

	inline std::string eXaDrums::GetKitDataFileName()
	{
		const char* str = this->GetKitDataFileName_();

		if(str == nullptr)
		{
			throw Util::Exception("Selected kit's path could not be found.", Util::error_type_error);
		}

		return std::string(str);		
	}

	inline void eXaDrums::RecorderExport(const std::string& fileName)
	{
		Util::ErrorToException([&]{ return RecorderExport_(fileName.data()); });
	}

	inline void eXaDrums::RecorderExportPCM(const std::string& fileName)
	{
		Util::ErrorToException([&]{ return RecorderExportPCM_(fileName.data()); });
	}

	inline void eXaDrums::RecorderPurgeTempFile()
	{
		Util::ErrorToException([&]{ return RecorderPurgeTempFile_(); });
	}

	inline std::vector<std::string> eXaDrums::GetClicksTypes()
	{

		unsigned int size;
		GetClicksTypes_(nullptr, size);

		std::vector<const char*> data(size);
		GetClicksTypes_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<int> eXaDrums::GetRhythms() const
	{

		unsigned int size;
		GetRhythms_(nullptr, size);

		std::vector<int> rhythms(size);
		GetRhythms_(rhythms.data(), size);

		return rhythms;
	}

	inline std::vector<int> eXaDrums::GetBpms() const
	{

		unsigned int size;
		GetBpms_(nullptr, size);

		std::vector<int> bpms(size);
		GetBpms_(bpms.data(), size);

		return bpms;
	}

	inline std::vector<std::string> eXaDrums::GetKitsNames()
	{

		unsigned int size;
		GetKitsNames_(nullptr, size);

		std::vector<const char*> data(size);
		GetKitsNames_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}

	inline std::vector<int> eXaDrums::GetInstrumentTriggersIds(std::size_t instrumentId) const
	{
		unsigned int size;
		GetInstrumentTriggersIds_(instrumentId, nullptr, size);

		std::vector<int> trigsIds(size);
		GetInstrumentTriggersIds_(instrumentId, trigsIds.data(), size);

		return trigsIds;
	}

	inline float eXaDrums::GetTriggerValue(size_t id)
	{
		float value = 0.f;
		Util::ErrorToException([&] { return this->GetTriggerValue_(id, value); });
		return value;
	}

	inline void eXaDrums::SetInstrumentVolume(std::size_t id, std::size_t volume)
	{
		Util::ErrorToException([&] { return this->SetInstrumentVolume_(id, volume); });
	}

	inline std::vector<std::string> eXaDrums::GetInstrumentsNames()
	{

		unsigned int size;
		GetInstrumentsNames_(nullptr, size);

		std::vector<const char*> data(size);
		GetInstrumentsNames_(data.data(), size);

		std::vector<std::string> v(size);
		std::copy(data.cbegin(), data.cend(), v.begin());

		return v;
	}


}


#endif /* SOURCE_API_EXADRUMS_HPP_ */
