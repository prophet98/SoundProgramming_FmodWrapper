#include "FmodConsole.h"
#include "pch.h"



void FmodConsole::PrintAllConsole()
{
	std::cout << "1) Load a sound\n";
	std::cout << "2) Load a sound (streaming)\n";
	std::cout << "3) Play sound\n";
	std::cout << "4) Play loop\n";
	std::cout << "5) Pause sound\n";
	std::cout << "6) Pause\n";
	std::cout << "7) Stop\n";
	std::cout << "8) Set Pan\n";
	std::cout << "9) Set Volume\n";
	std::cout << "H) Help\n";
	std::cout << "F) Exit\n";
}


FmodConsole::FmodConsole()
{
	PrintAllConsole();
}

