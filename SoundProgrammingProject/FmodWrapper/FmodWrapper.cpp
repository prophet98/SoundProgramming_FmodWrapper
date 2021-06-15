
#include "pch.h"
#include "framework.h"
#include "FmodWrapper.h"
#define PATH_MAX_LENGTH 255
using namespace FMOD;

CustomWrapper::CustomWrapper(int channelNumber)
{
	FMOD_RESULT result;
	mChannel = new FMOD::Channel * [channelNumber];
	result = System_Create(&mSystem);
	std::cout << R"(
______                   _   _    _                                 
|  ___|                 | | | |  | |                                
| |_ _ __ ___   ___   __| | | |  | |_ __ __ _ _ __  _ __   ___ _ __ 
|  _| '_ ` _ \ / _ \ / _` | | |/\| | '__/ _` | '_ \| '_ \ / _ \ '__|
| | | | | | | | (_) | (_| | \  /\  / | | (_| | |_) | |_) |  __/ |   
\_| |_| |_| |_|\___/ \__,_|  \/  \/|_|  \__,_| .__/| .__/ \___|_|   
                                             | |   | |              
                                             |_|   |_|  )" << '\n';
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
	userMaxChannels = channelNumber;
	std::cout << "Initializing FmodSystem...\nChecking Errors..." << std::endl;
	std::cout << FMOD_ErrorString(result) << "\n\n";

	char soundPath[PATH_MAX_LENGTH];

	GetCurrentDir(soundPath, PATH_MAX_LENGTH);

	if (absoulutePath.empty())
	{
		absoulutePath = std::string(soundPath);
	}

	std::cout << "Your sounds must be inside the following path or else they wont be played: \n" << absoulutePath.c_str() << std::endl << std::endl;

}


CustomWrapper::~CustomWrapper()
{
	mSystem->release();
	mSystem = nullptr;
	delete mChannel;
	mChannel = nullptr;
}

int CustomWrapper::LoadSound(const std::string soundName, bool isLooping, bool isStream)
{
	FMOD::Sound* soundPtr;

	FMOD_RESULT result{};
	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= isStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	result = mSystem->createSound(soundName.c_str(), eMode, 0, &soundPtr);
	if (result != FMOD_OK)
	{
		std::cout << "The sound source could not be found \n";
		return -1;
	}
	std::cout << "The sound source has been loaded \n";

	mSounds[soundIndex] = soundPtr;
	soundIndex++;
	return soundIndex - 1;
}

int CustomWrapper::PlaySoundOnChannel(int sourceIndex, int channelNumber)
{
	FMOD::Sound* sound;
	FMOD::Channel* ch;
	channelNumber--; //decrement so that we use the correct index inside the array, increment it later to show it to the player.
	FMOD_RESULT result;

	sound = mSounds[sourceIndex];
	ch = mChannel[channelNumber];

	bool isPlaying = false;
	ch->isPlaying(&isPlaying);
	bool isPaused = false;
	ch->getPaused(&isPaused);

	if (isPaused)
	{
		std::cout << "There was a paused sound here!...\n";
		ch->setPaused(false);
	}
	else if (isPlaying)
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

		mChannel[channelNumber] = ch;
		mChannelsMap[channelNumber] = channelNumber + 1; //increment by one because I do not want the channels to be 0 based.
		return 0;
	}

	return -1;

}
int CustomWrapper::StopSoundOnChannel(int channelNumber)
{
	FMOD::Channel* channel;
	FMOD_RESULT result;
	channelNumber--;
	channel = mChannel[channelNumber];
	bool isPlaying = false;
	channel->isPlaying(&isPlaying);
	if (isPlaying)
	{
		result = channel->stop();
		if (result != FMOD_OK)
		{
			return -1;
		}

		mChannelsMap[channelNumber] = 0;
		std::cout << "Stopping Channel... \n";
		return 0;
	}
	else
	{
		std::cout << "There is no sound to be stopped on this channel\n";
		return -1;
	}

}

int CustomWrapper::PauseSoundOnChannel(int channelNumber)
{
	FMOD::Channel* channel;
	FMOD_RESULT result;
	channelNumber--;
	channel = mChannel[channelNumber];
	bool isPlaying = false;
	channel->isPlaying(&isPlaying);
	if (isPlaying)
	{
		result = channel->setPaused(true);
		if (result != FMOD_OK)
		{
			return -1;
		}
		std::cout << "Pausing Channel... \n";
		return 0;
	}
	else
	{
		std::cout << "There is no sound to be paused on this channel\n";
		return -1;
	}
}

int CustomWrapper::SetSoundVolumeOnChannel(int channelNumber, float volume)
{
	FMOD::Channel* channel;
	FMOD_RESULT result;
	channelNumber--;
	channel = mChannel[channelNumber];
	bool isPlaying = false;
	channel->isPlaying(&isPlaying);
	if (isPlaying)
	{
		result = channel->setVolume(volume);
		if (result != FMOD_OK)
		{
			return -1;
		}
		std::cout << "Modifying Channel Volume... \n";
		return 0;
	}
	else
	{
		std::cout << "There is no active sound on this channel\n";
		return -1;
	}
}

int CustomWrapper::SetSoundPanOnChannel(int channelNumber, float panValue)
{
	FMOD::Channel* channel;
	FMOD_RESULT result;
	channelNumber--;
	channel = mChannel[channelNumber];
	bool isPlaying = false;
	channel->isPlaying(&isPlaying);
	if (isPlaying)
	{
		result = channel->setPan(panValue);
		if (result != FMOD_OK)
		{
			return -1;
		}
		std::cout << "Modifying Channel Pan... \n";
		return 0;
	}
	else
	{
		std::cout << "There is no active sound on this channel\n";
		return -1;
	}
}

void CustomWrapper::PrintChannelState()
{
	bool isChannelInUse = false;
	for (int i = 0; i < userMaxChannels; i++)
	{
		if (mChannelsMap[i] != 0)
		{
			std::cout << "You are currently using channel number : " << i + 1 << std::endl;
			isChannelInUse = true;
		}
	}
	if (!isChannelInUse)
	{
		std::cout << "There are no active playing channels at the moment, please play a loaded sound in a channel.\n" << std::endl;
	}
}
