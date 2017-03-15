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


	TriggerParameters::TriggerParameters()
	{
		*this = DrumKit::TriggerParameters();
		return;
	}

	TriggerParameters::TriggerParameters(const DrumKit::TriggerParameters& parameters)
	{
		*this = parameters;
		return;
	}

	TriggerParameters& TriggerParameters::operator=(const DrumKit::TriggerParameters& parameters)
	{

		std::string typeStr = Enums<DrumKit::TriggerType>::ToString(parameters.type);
		if(typeStr.length() > sizeof(this->type))
		{
			throw -1;
		}

		std::string responseStr = Enums<DrumKit::CurveType>::ToString(parameters.response);
		if(responseStr.length() > sizeof(this->response))
		{
			throw -1;
		}

		std::strcpy(this->type, typeStr.c_str());
		std::strcpy(this->response, responseStr.c_str());

		this->maskTime = parameters.maskTime;
		this->scanTime = parameters.scanTime;
		this->sensorId = parameters.sensorId;
		this->threshold = parameters.threshold;

		return *this;
	}

	TriggerParameters::operator DrumKit::TriggerParameters() const
	{

		DrumKit::TriggerParameters parameters;

		parameters.type = Enums<DrumKit::TriggerType>::ToElement(std::string(this->type));
		parameters.response = Enums<DrumKit::CurveType>::ToElement(std::string(this->response));

		parameters.maskTime = this->maskTime;
		parameters.scanTime = this->scanTime;
		parameters.sensorId = this->sensorId;
		parameters.threshold = this->threshold;

		return parameters;
	}


}


