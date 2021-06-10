#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fmod.hpp>
#include <fmod_errors.h>

class CustomWrapper
{
public:
	CustomWrapper(int channelNumber);
	~CustomWrapper();

	int LoadSound(const std::string, bool, bool);

	int PlaySoundOnChannel(int, int);

	int StopSoundOnChannel(int);

	int PauseSoundOnChannel(int);

	int SetSoundVolumeOnChannel(int, float);
private:

	FMOD::System* mSystem;

	FMOD::Sound* mySoundPtr = nullptr;
	std::map<int, FMOD::Sound*> mySounds;
	int soundIndex;

	std::map<int, int> myChannelsMap;
	FMOD::Channel** myChannels = nullptr;
	int m_AvailableChannels;
};
