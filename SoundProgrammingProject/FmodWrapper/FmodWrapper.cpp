// FmodWrapper.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "FmodWrapper.h"

using namespace FMOD;

CustomWrapper::CustomWrapper()
{
	myResult = System_Create(&mySystem);
	myResult = mySystem->init(8, FMOD_INIT_NORMAL, NULL);

	if (myResult != FMOD_OK)
	{
		std::cout << "FMOD error:  " << myResult << "  " << FMOD_ErrorString(myResult) << std::endl;
		exit(-1);
	}

	myResult = mySystem->getMasterChannelGroup(&myMasterChannelGroup);

	std::cout << FMOD_ErrorString(myResult) << std::endl;
}

CustomWrapper::~CustomWrapper()
{
	myMasterChannelGroup->release();
}

FMOD_RESULT CustomWrapper::LoadSound(const std::string soundName, bool is3d, bool isLooping, bool isStream)
{
	auto foundIterator = mySounds.find(soundName);
	if (foundIterator != mySounds.end())
	{
		return FMOD_OK;
	}

	FMOD_MODE soundMode = FMOD_DEFAULT;
	soundMode |= is3d ? FMOD_3D : FMOD_2D;
	soundMode |= isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	soundMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	FMOD::Sound* soundPtr = nullptr;

	myResult = mySystem->createSound(soundName.c_str(), soundMode, 0, &soundPtr);
	if (soundPtr)
	{
		mySounds[soundName] = soundPtr;
	}

	return myResult;
}

