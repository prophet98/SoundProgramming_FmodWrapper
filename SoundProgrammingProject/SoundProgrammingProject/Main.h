#pragma once
#include <algorithm>

CustomWrapper* customWrapper;
FmodConsole* console;

void HandleInput(char input);
void LoadSound();
void PlaySound();
void StopSound();
void PauseSound();
void SetSoundVolume();
void SetPanVolume();

int GetSoundOptions();
int maxChannels = 8; //modify this to change the maximum number of channels 
bool isProgramClosed;

inline bool is_number(const std::string& s) //check if the passed string is a number
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
