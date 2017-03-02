/*
 * Config_api.h
 *
 *  Created on: 2 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_API_CONFIG_API_H_
#define SOURCE_API_CONFIG_API_H_


namespace eXaDrumsApi
{

	class eXaDrums;

	class Config
	{

	public:

		Config(eXaDrums& drums);
		virtual ~Config() = default;

	private:

		eXaDrums& drumKit;



	};

}

#endif /* SOURCE_API_CONFIG_API_H_ */
