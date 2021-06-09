#pragma once
#include <iostream>

class FmodConsole
{
public:
	FmodConsole();
	~FmodConsole();

private:
	void TakeInput();
	void RefreshScreen();
	void RenderScreen();

	void PrintAllConsole();

};