/*
 * Kit.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#include "Kit.h"

namespace DrumKit
{

	Kit::Kit(KitParameters params) : parameters(params)
	{

		return;
	}

	Kit::~Kit()
	{

		return;
	}

	std::string Kit::GetInstrumentName(std::size_t id) const
	{

		if(id > parameters.instrumentParameters.size())
		{
			throw -1;
		}

		std::string name = parameters.instrumentParameters[id].instrumentName;

		return name;
	}


} /* namespace DrumKit */
