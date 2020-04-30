/*
 * TriggerParameters.cpp
 *
 *  Created on: 14 Mar 2017
 *      Author: jeremy
 */


#include "TriggerParameters_api.h"

#include "../../DrumKit/Triggers/TriggerParameters.h"
#include "../../Util/Enums.h"

#include <string>

#include <cstring>

using namespace Util;

namespace eXaDrumsApi
{


	TriggerParameters::TriggerParameters() noexcept
	{
		*this = DrumKit::TriggerParameters();
		return;
	}

	TriggerParameters::TriggerParameters(const DrumKit::TriggerParameters& parameters) noexcept
	{
		*this = parameters;
		return;
	}

	TriggerParameters& TriggerParameters::operator=(const DrumKit::TriggerParameters& parameters) noexcept
	{

		std::string typeStr = Enums::ToString(parameters.type);

		std::string responseStr = Enums::ToString(parameters.response);

		std::snprintf(this->type, sizeof this->type, "%s", typeStr.data());
		std::snprintf(this->response, sizeof this->response, "%s", responseStr.data());
		this->maskTime = parameters.maskTime;
		this->scanTime = parameters.scanTime;
		this->sensorId = parameters.sensorId;
		this->threshold = parameters.threshold;
		this->gain = parameters.gain;

		return *this;
	}

	TriggerParameters::operator DrumKit::TriggerParameters() const
	{

		DrumKit::TriggerParameters parameters;

		parameters.type = Enums::ToElement<DrumKit::TriggerType>(std::string(this->type));
		parameters.response = Enums::ToElement<DrumKit::CurveType>(std::string(this->response));

		parameters.maskTime = this->maskTime;
		parameters.scanTime = this->scanTime;
		parameters.sensorId = this->sensorId;
		parameters.threshold = this->threshold;
		parameters.gain = this->gain;

		return parameters;
	}


}


