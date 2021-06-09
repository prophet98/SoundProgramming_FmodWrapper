#pragma once

std::string SoundPath = "D:\\C++ Projects\\SoundProgramming\\SoundProgrammingProject\\";
CustomWrapper* myPlayer;
bool isProgramClosed;
int maxChannels = 8;
void HandleInput(char input);
void LoadSound();
void PlaySound();
void StopSound();