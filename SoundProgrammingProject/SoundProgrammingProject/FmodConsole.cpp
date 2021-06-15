#include "FmodConsole.h"
#include "FmodWrapper.h"
#include "pch.h"

void FmodConsole::RefreshScreen()
{
	system("cls");
}

void FmodConsole::PrintAllConsole()
{
	std::cout << "1) Load a sound\n";
	std::cout << "2) Play sound\n";
	std::cout << "3) Pause sound\n";
	std::cout << "4) Stop sound\n";
	std::cout << "5) Set Pan\n";
	std::cout << "6) Set Volume\n";
	std::cout << "7) Wrapper instruction help\n";
	std::cout << "8) Print channel status\n";
	std::cout << "9) Quit Application\n";
}

void FmodConsole::PrintInstructions()
{
	RefreshScreen();

	std::cout << "You first need to load a sound with the command by using the correct case sensitive name of the sound. \n";
	std::cout << "After that you will be able to play it on any of the available channels, which are the ones without a playing or paused sound on it\n";
	std::cout << "Each sound is specified with a 0 based index and the channels start at 1.\n\n\n";

	PrintAllConsole();
}

FmodConsole::FmodConsole()
{
	PrintAllConsole();
}

