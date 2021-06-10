#pragma once
#include <algorithm>
std::string SoundPath = "D:\\C++ Projects\\SoundProgramming\\SoundProgrammingProject\\";
CustomWrapper* myPlayer;
bool isProgramClosed;
int maxChannels = 8;
void HandleInput(char input);
int GetSoundOptions();
void LoadSound();
void PlaySound();
void StopSound();
void PauseSound();
void SetSoundVolume();
void SetPanVolume();

inline bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}