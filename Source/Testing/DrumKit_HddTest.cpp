/*
 * DrumKit.cpp
 *
 *  Created on: 25 May 2015
 *      Author: jeremy
 */

#include "DrumKit_HddTest.h"

namespace Testing
{

	void DrumKit_HddTest::RunTest()
	{


		std::string workingDirectory("/home/jeremy/Desktop/Prog/RaspiDrums/Data/");
		std::string kitLocation(workingDirectory + "Kits/default.xml");


		DrumKit::Kit kit;

		DrumKit::Module module(workingDirectory);
		module.LoadKit(kitLocation, kit);


		std::string xmlFileLoc(workingDirectory + "alsaConfig.xml");

		Sound::AlsaParams aParams;
		Sound::Alsa::ReadXmlConfig(aParams, xmlFileLoc);


		Sound::Mixer mixer(module.soundParameters, aParams);
		Sound::Alsa  alsa(aParams, mixer);

		std::string sensorFile(workingDirectory + "../out.raw");

		IO::HddSensor hddSensor(sensorFile);
		DrumKit::Trigger snareTrigger(kit.drum[0], mixer);

		alsa.Start();

		int N = hddSensor.GetDataLength();

		for(int i = 0; i < N; i++)
		{

			short value = hddSensor.GetOutput();
			snareTrigger.Trig(value);

		}

		alsa.Stop();


		return;
	}


}
