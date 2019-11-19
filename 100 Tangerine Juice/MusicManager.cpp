#include "MusicManager.h"
#include "Globals.h"

/*
	MusicManager

	Play musics with the help of this manager.
*/

Mix_Music* MusicManager::musicSource = nullptr;

void MusicManager::playMusic(const string path, const int loops)
{
	MusicManager::musicSource = Globals::resources->createMusic(path);
	if (Mix_PlayMusic(MusicManager::musicSource, loops) == -1)
	{
		SDL_Log("MusicManager::playMusic - Cannot play the music due to an error: %s", Mix_GetError());
	}

	Mix_VolumeMusic(25);
}

void MusicManager::setMusicVolume(const int volume)
{
	Mix_VolumeMusic(volume);
}

// Speed being in milliseconds
void MusicManager::fadeOutMusic(const int speed)
{
	Mix_FadeOutMusic(speed);
}

void MusicManager::stopMusic()
{
	Mix_HaltMusic();
}