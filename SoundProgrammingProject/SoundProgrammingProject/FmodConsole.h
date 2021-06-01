#pragma once

class FmodConsole
{
public:
	FmodConsole();
	~FmodConsole();

private:
	void TakeInput();
	void RefreshScreen();
	void RenderScreen();
};