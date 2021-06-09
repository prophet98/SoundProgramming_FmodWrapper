#include <iostream>
#include "FmodWrapper.h"
#include "FmodConsole.h"
#include "Main.h"

#define GetCurrentDir _getcwd 
#define PATH_MAX_LENGTH 255 GetCurrentDir(c_absolute_path, PATH_MAX_LENGTH);

int main()
{
	std::cout << "Welcome to the Custom Fmod Wrapper created by Alessandro Sciarra. \n\n\n";
	myPlayer = new CustomWrapper(maxChannels);
	FmodConsole* console = new FmodConsole();

	char input;

	while (!isProgramClosed)
	{
		std::cin >> input;

		HandleInput(input);
	}
	return 0;
}

void HandleInput(char input)
{
	switch (input)
	{
	case 49: //1
	{
		std::cout << "Loading sound..." << std::endl;
		LoadSound();
		break;
	}
	case 50: //2 
	{
		isProgramClosed = true;
		break;
	}
	case 51: //3 
	{
		PlaySound();
		break;
	}
	case 52: //4
	{

		break;
	}
	case 53: //5
	{
		StopSound();
		break;
	}
	default:
	{
		break;
	}
	}

}

void LoadSound()
{
	std::cout << "\nInsert audio source name: ";
	std::cin.ignore();
	std::string new_resource_file_name;
	getline(std::cin, new_resource_file_name);
	int soundIndex = myPlayer->LoadSound(SoundPath + new_resource_file_name, 50.0f, true, false, false);
	if (soundIndex >= 0)
	{
		std::cout << "Loaded sound index is :" << soundIndex << std::endl;
	}
}

void PlaySound()
{
	std::cout << "Choose source index: ";
	std::cin.ignore();
	std::string new_source_id;
	getline(std::cin, new_source_id);
	int source_id;

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
		int result = myPlayer->PlaySoundOnChannel(source_id, channel);
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
		int result = myPlayer->StopSoundOnChannel(channel);
		if (result == -1)
			return;
		else
			std::cout << "Channel has been stopped \n";
	}
}
