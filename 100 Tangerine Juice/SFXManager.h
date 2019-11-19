#pragma once
#include <string>
#include <SDL_mixer.h>

using std::string;

class SFXManager
{
private:
	static Mix_Chunk* soundEffect;

public:
	static void playSFX(const string sfxIdentifier);
	static void playSFXPath(const string path);
};
