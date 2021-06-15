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

	std::string absoulutePath;

	int LoadSound(const std::string, bool, bool);

	int PlaySoundOnChannel(int, int);

	int StopSoundOnChannel(int);

	int PauseSoundOnChannel(int);

	int SetSoundVolumeOnChannel(int, float);

	int SetSoundPanOnChannel(int, float);

	void PrintChannelState();

private:

	FMOD::System* mSystem;

	std::map<int, FMOD::Sound*> mSounds;
	int soundIndex = 0;

	int userMaxChannels = 0;
	std::map<int, int> mChannelsMap;
	FMOD::Channel** mChannel = nullptr;
};
