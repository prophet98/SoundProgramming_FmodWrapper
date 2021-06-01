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
	CustomWrapper();
	~CustomWrapper();

	FMOD_RESULT LoadSound(const std::string, float, bool, bool, bool);
	FMOD_RESULT UnloadSound(const std::string&);

	bool SoundWasLoaded(const std::string&);

	FMOD_RESULT PlayChannel(int);

	FMOD_RESULT StopChannel(int);

	FMOD_RESULT PauseChannel(int);

	void IncreaseChannelVolume(int);
	void DecreaseChannelVolume(int);
	float channelVolume;

	void CenterChannelPan(int);
	void MoveChannelPanRight(int);
	void MoveChannelPanLeft(int);
	float channelPanLevel = 0.0f;
	std::vector<float>* channelPanLevels = new std::vector<float>();

private:
	FMOD::Sound* mySoundPtr = nullptr;
	FMOD_CREATESOUNDEXINFO mySoundInfo;
	bool playingChannelState;

	int nextChannel;
	std::map<std::string, FMOD::Sound*> mySounds;
	std::map<int, FMOD::Channel*> myChannels;
	std::map<int, FMOD::Sound*> mySoundsOnChannels;

	bool bChannelIsPlaying;
	unsigned int iChannelPosition;
	float chanPositionInSec;
	std::wstring outputString;

	FMOD::System* mSystem;
	FMOD::ChannelGroup* myMasterChannelGroup;
	FMOD_RESULT mResult;
};
