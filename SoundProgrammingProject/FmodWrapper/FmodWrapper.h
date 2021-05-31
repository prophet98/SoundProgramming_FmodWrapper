#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <string>
#include <map>

class CustomWrapper
{
public:
	CustomWrapper();
	~CustomWrapper();

	typedef std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;
	typedef std::map<int, FMOD::Sound*> PlayedSoundsMap;

	FMOD_RESULT LoadSound(const std::string, bool, bool, bool);
	FMOD_RESULT UnloadSound(const std::string&);
	//FMOD_RESULT LoadSoundOnEmptyChannel(const std::string& strSoundName, const Vector3& vPosition, float volumedB, bool, bool, bool);
	bool SoundWasLoaded(const std::string&);
	bool ChannelIsUsed(int);
	FMOD_RESULT ChangeOptsOfLoadedSound(const std::string&, bool, bool, bool);
	FMOD_RESULT  GetOptsOfLoadedSound(const std::string&, bool*, bool*, bool*);

	FMOD_RESULT PlayChannel(int);
	FMOD_RESULT PlayAllChannels();

	FMOD_RESULT StopChannel(int);
	FMOD_RESULT StopAllChannels();

	FMOD_RESULT PauseAllChannels();

	std::wstring& DisplayChannelsState();

	void IncreaseChannelVolume(int);
	void DecreaseChannelVolume(int);
	float channelVolume;
	void CenterChannelPan(int);
	void MoveChannelPanRight(int);
	void MoveChannelPanLeft(int);
	float channelPanLevel = 0.0f;
private:
	FMOD::Sound* mySoundPtr = nullptr;
	FMOD_CREATESOUNDEXINFO mySoundInfo;
	bool playingChannelState;

	int nextChannel;
	SoundMap mySounds;
	ChannelMap myChannels;
	PlayedSoundsMap mySoundsOnChannels;

	//std::vector<ChannelMap::iterator> stoppedChannels;
	bool bChannelIsPlaying;
	unsigned int iChannelPosition;
	float chanPositionInSec;
	std::wstring outputString;

	FMOD::System* mySystem;
	FMOD::ChannelGroup* myMasterChannelGroup;
	FMOD_RESULT myResult;
};
