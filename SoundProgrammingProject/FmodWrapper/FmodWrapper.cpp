// FmodWrapper.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "FmodWrapper.h"

using namespace FMOD;

CustomWrapper::CustomWrapper()
{
	mResult = System_Create(&mSystem);
	mResult = mSystem->init(8, FMOD_INIT_NORMAL, NULL);

	if (mResult != FMOD_OK)
	{
		std::cout << "FMOD error:  " << mResult << "  " << FMOD_ErrorString(mResult) << std::endl;
		exit(-1);
	}

	mResult = mSystem->getMasterChannelGroup(&myMasterChannelGroup);

	std::cout << FMOD_ErrorString(mResult) << std::endl;
}

CustomWrapper::~CustomWrapper()
{
	myMasterChannelGroup->release();
}

FMOD_RESULT CustomWrapper::LoadSound(const std::string soundName, float volume, bool is3d, bool isLooping, bool isStream)
{
	auto foundIterator = mySounds.find(soundName);
	if (foundIterator != mySounds.end())
	{
		return FMOD_OK;
	}
	else
	{
		return FMOD_ERR_FILE_NOTFOUND;
	}

	FMOD_MODE soundMode = FMOD_DEFAULT;
	soundMode = FMOD_2D;
	soundMode |= isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	soundMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	FMOD::Sound* soundPtr = nullptr;

	mResult = mSystem->createSound(soundName.c_str(), soundMode, 0, &soundPtr);
	if (soundPtr)
	{
		mySounds[soundName] = soundPtr;
	}

	Channel* myChannel = nullptr;

	mResult = mSystem->playSound(foundIterator->second, myMasterChannelGroup, true, &myChannel);
	if (myChannel)
	{
		FMOD_MODE currentMode;
		mResult = foundIterator->second->getMode(&currentMode);

		mResult = myChannel->setVolume(volume);
		mResult = myChannel->setPaused(false);

		myChannels.emplace(std::make_pair(nextChannel, myChannel));
		mySoundsOnChannels.emplace(std::make_pair(nextChannel, foundIterator->second));
		channelPanLevels->push_back(0.0f);
		++nextChannel;
	}
	else
	{

	}

	return mResult;
}

FMOD_RESULT CustomWrapper::PlayChannel(int channelNumber)
{
	auto foundChannelIt = myChannels.find(channelNumber);
	if (foundChannelIt != myChannels.end())
	{

		foundChannelIt->second->isPlaying(&playingChannelState);
		if (!playingChannelState)
		{
			mSystem->playSound(mySoundsOnChannels[foundChannelIt->first], myMasterChannelGroup, false, &(foundChannelIt->second));
		}
	}
	return FMOD_OK;
}
FMOD_RESULT CustomWrapper::StopChannel(int channelNumber)
{
	auto foundChannelIt = myChannels.find(channelNumber);
	if (foundChannelIt != myChannels.end())
	{
		return foundChannelIt->second->stop();
	}
	return FMOD_OK;
}