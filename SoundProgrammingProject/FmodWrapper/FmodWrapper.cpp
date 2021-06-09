// FmodWrapper.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "FmodWrapper.h"

using namespace FMOD;

CustomWrapper::CustomWrapper(int channelNumber)
{
	FMOD_RESULT result;
	myChannels = new FMOD::Channel * [channelNumber];

	result = System_Create(&mSystem);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error:  " << result << "  " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
	result = mSystem->init(channelNumber, FMOD_INIT_NORMAL, NULL);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error:  " << result << "  " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	std::cout << "Initializing FmodSystem...\nChecking Errors..." << std::endl;
	std::cout << FMOD_ErrorString(result) << std::endl;

	std::cout << "\n\n";
}


CustomWrapper::~CustomWrapper()
{
	//myMasterChannelGroup->release();
}

int CustomWrapper::LoadSound(const std::string soundName, float volume, bool is3d, bool isLooping, bool isStream)
{

	FMOD::Sound* soundPtr;
	FMOD::Channel* ch;

	FMOD_RESULT result{};
	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= is3d ? FMOD_3D : FMOD_2D;
	eMode |= isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	result = mSystem->createSound(soundName.c_str(), eMode, 0, &soundPtr);
	if (result != FMOD_OK)
	{
		std::cout << "The sound source could not be found \n";
		return -1;
	}
	std::cout << "The sound source has been loaded \n";

	mySounds[soundIndex] = soundPtr;
	soundIndex++;
	return soundIndex - 1;
}

int CustomWrapper::PlaySoundOnChannel(int sourceIndex, int channelNumber)
{
	FMOD::Sound* sound;
	FMOD::Channel* ch;
	channelNumber--;
	FMOD_RESULT result;

	sound = mySounds[sourceIndex];
	ch = myChannels[channelNumber];
	//int play_channel = myChannelsMap[sourceIndex];

	bool isPlaying = false;

	ch->isPlaying(&isPlaying);
	if (isPlaying)
	{
		std::cout << "There is already a sound on this channel! \nStop it before trying to play another one.\n";
		return -1;
	}
	else
	{
		result = mSystem->playSound(sound, 0, false, &ch);

		if (result != FMOD_OK)
		{
			std::cout << "Could not be played \n";
			return -1;
		}

		myChannels[channelNumber] = ch;
		myChannelsMap[sourceIndex] = channelNumber;
		return 0;
	}

}
int CustomWrapper::StopSoundOnChannel(int channelNumber)
{
	FMOD::Channel* channel;
	FMOD_RESULT result;
	channelNumber--;
	channel = myChannels[channelNumber];
	bool isPlaying = false;
	channel->isPlaying(&isPlaying);
	if (isPlaying)
	{
		result = channel->stop();
		if (result != FMOD_OK)
		{
			return -1;
		}

		myChannelsMap[channelNumber] = 0;
		std::cout << "Stopping Channel... \n";
		return 0;
	}
	else
	{
		std::cout << "There is no active sound on this channel\n";
		return -1;
	}
	
}