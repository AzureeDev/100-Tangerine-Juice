#include "SFXManager.h"
#include "Globals.h"

Mix_Chunk* SFXManager::soundEffect = nullptr;
const int SFX_VOLUME = 30;

void SFXManager::playSFX(const string sfxIdentifier)
{
	SFXManager::soundEffect = Globals::resources->createSFX("assets/sfx/" + sfxIdentifier + ".wav");
	Mix_VolumeChunk(SFXManager::soundEffect, SFX_VOLUME);
	Mix_PlayChannel(-1, SFXManager::soundEffect, 0);
}

void SFXManager::playSFXPath(const string path)
{
	SFXManager::soundEffect = Globals::resources->createSFX(path);
	Mix_VolumeChunk(SFXManager::soundEffect, SFX_VOLUME);
	Mix_PlayChannel(-1, SFXManager::soundEffect, 0);
}