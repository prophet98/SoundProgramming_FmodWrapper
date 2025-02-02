#include "FmodWrapper.h"
#include "FmodConsole.h"
#include "Main.h"

int main()
{
	std::cout << "Sound programming exam Alessandro Sciarra -- UniVR.\n";
	customWrapper = new CustomWrapper(maxChannels);
	std::cout << "You are currently using " << maxChannels << " channels.\n\n";
	console = new FmodConsole();

	char input;

	while (!isProgramClosed)
	{
		std::cin >> input;

		HandleInput(input);
	}
	delete customWrapper;
	customWrapper = nullptr;
	delete console;
	console = nullptr;
	return 0;
}

void HandleInput(char input)
{
	switch (input)
	{
	case 49: //1
	{
		LoadSound();
		break;
	}
	case 50: //2 
	{
		PlaySound();
		break;
	}
	case 51: //3 
	{
		PauseSound();
		break;
	}
	case 52: //4
	{
		StopSound();
		break;
	}
	case 53: //5
	{
		SetPanVolume();
		break;
	}
	case 54: //6
	{
		SetSoundVolume();
		break;
	}
	case 55: //7
	{
		console->PrintInstructions();
		break;
	}
	case 56: //8
	{
		customWrapper->PrintChannelState();
		break;
	}
	case 57: //9
	{
		isProgramClosed = true;
		break;
	}
	default:
	{
		break;
	}
	}

}

int GetSoundOptions()
{
	std::cout << "\nInsert audio source name: ";
	std::cin.ignore();
	std::string soundFileName;
	getline(std::cin, soundFileName);

	std::cout << "Allow sound looping?\n";
	std::string isLoopingInput;
	bool isLooping;
	do
	{
		std::cin.clear();
		std::cout << "Enter Y or N: ";
		std::cin >> isLoopingInput;

	} while ((isLoopingInput.length() != 1) || (isLoopingInput[0] != 'y' && isLoopingInput[0] != 'n' && isLoopingInput[0] != 'Y' && isLoopingInput[0] != 'N'));

	if (tolower(isLoopingInput[0]) == 'y')
	{
		isLooping = true;
	}
	else
	{
		isLooping = false;
	}

	std::cout << "Load sound in streaming mode?\n";
	std::cin.ignore();
	std::string isStreamInput;
	bool isStreaming;
	do
	{
		std::cin.clear();
		std::cout << "Enter Y or N: ";
		std::cin >> isStreamInput;

	} while ((isStreamInput.length() != 1) || (isStreamInput[0] != 'y' && isStreamInput[0] != 'n' && isStreamInput[0] != 'Y' && isStreamInput[0] != 'N'));
	if (tolower(isStreamInput[0]) == 'y')
	{
		isStreaming = true;
	}
	else
	{
		isStreaming = false;
	}

	int soundIndex = customWrapper->LoadSound(customWrapper->absoulutePath + "\\" + soundFileName, isLooping, isStreaming);
	if (soundIndex >= 0)
	{
		std::cout << "Loaded sound index is :" << soundIndex << std::endl;
		return 0;
	}
	return -1;
}

void LoadSound()
{
	std::cout << "Loading sound..." << std::endl;
	GetSoundOptions();
}

void PlaySound()
{
	std::cout << "Choose source index: ";
	std::cin.ignore();
	std::string new_source_id;
	getline(std::cin, new_source_id);
	int source_id = 0;

	if (!new_source_id.empty())
	{
		source_id = atoi(new_source_id.c_str());
	}
	std::cout << "Choose channel to slot in this source: ";

	std::string new_channels;
	getline(std::cin, new_channels);
	int channel = 0;
	if (!new_channels.empty())
	{
		channel = atoi(new_channels.c_str());
	}

	if (channel < 1 || channel > maxChannels)
	{
		std::cout << "FMod Channel Error \n";
	}
	else
	{
		int result = customWrapper->PlaySoundOnChannel(source_id, channel);
		if (result == -1)
			return;
		else
			std::cout << "Playing sound... \n";
	}
}

void StopSound()
{
	std::cout << "Choose channel to stop: ";
	std::cin.ignore();
	std::string new_channels;
	getline(std::cin, new_channels);
	int channel = 0;
	if (!new_channels.empty())
	{
		channel = atoi(new_channels.c_str());
	}

	if (channel < 1 || channel > maxChannels)
	{
		std::cout << "FMod Channel Error \n";
	}
	else
	{
		int result = customWrapper->StopSoundOnChannel(channel);
		if (result == -1)
			return;
		else
			std::cout << "Channel has been stopped \n";
	}
}

void PauseSound()
{
	std::cout << "Choose channel to pause: ";
	std::cin.ignore();
	std::string new_channels;
	getline(std::cin, new_channels);
	int channel = 0;
	if (!new_channels.empty())
	{
		channel = atoi(new_channels.c_str());
	}

	if (channel < 1 || channel > maxChannels)
	{
		std::cout << "FMod Channel Error \n";
	}
	else
	{
		int result = customWrapper->PauseSoundOnChannel(channel);
		if (result == -1)
			return;
		else
			std::cout << "Channel has been paused \n";
	}
}

void SetSoundVolume()
{
	std::cout << "Select a channel: ";
	std::cin.ignore();
	std::string new_channels;
	getline(std::cin, new_channels);
	int channel = 0;
	if (!new_channels.empty())
	{
		channel = atoi(new_channels.c_str());
	}

	if (channel < 1 || channel > maxChannels)
	{
		std::cout << "FMod Channel Error \n";
	}
	else
	{
		std::string channelVolume;
		float newVolume;
		do
		{
			std::cin.clear();
			std::cout << "Enter the new volume for this channel [1 to 10]: ";
			std::cin >> channelVolume;

		} while (!is_number(channelVolume) || (std::stof(channelVolume) > 10 || std::stof(channelVolume) < 1));

		newVolume = std::stof(channelVolume) / 10;
		int result = customWrapper->SetSoundVolumeOnChannel(channel, newVolume);
		if (result == -1)
			return;
		else
			std::cout << "Volume has been changed \n";
	}
}

void SetPanVolume()
{
	std::cout << "Select a channel: ";
	std::cin.ignore();
	std::string new_channels;
	getline(std::cin, new_channels);
	int channel = 0;
	if (!new_channels.empty())
	{
		channel = atoi(new_channels.c_str());
	}

	if (channel < 1 || channel > maxChannels)
	{
		std::cout << "FMod Channel Error \n";
	}
	else
	{
		std::string channelPan;
		float newPan;
		do
		{
			std::cin.clear();
			std::cout << "Enter the new pan for this channel [-10 to 10]: ";
			std::cin >> channelPan;

		} while (!is_number(channelPan) && (std::stof(channelPan) > 10 || std::stof(channelPan) < -10));

		newPan = std::stof(channelPan) / 10;
		int result = customWrapper->SetSoundPanOnChannel(channel, newPan);
		if (result == -1)
			return;
		else
			std::cout << "Pan has been changed \n";
	}
}
