/*
 * SoundBank.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jeremy
 */

#ifndef SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_
#define SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_

#include <string>
#include <vector>
#include <fstream>

namespace Sound
{

	class SoundBank
	{

	public:

		SoundBank();
		virtual ~SoundBank();

		static void LoadSound(std::string filename, std::vector<short>& data, unsigned int& duration);


	private:



	};

} /* namespace Sound */

#endif /* SOURCE_SOUND_SOUNDBANK_SOUNDBANK_H_ */
