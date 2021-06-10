#include "FmodConsole.h"
#include "pch.h"



void FmodConsole::RefreshScreen()
{
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
	std::cout << "8) Quit Application\n";
}


FmodConsole::FmodConsole()
{
	PrintAllConsole();
}

