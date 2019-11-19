#pragma once
#include <string>
#include <SDL_mixer.h>

using std::string;

class MusicManager
{
private:
	static Mix_Music* musicSource;

public:
	static void playMusic(const string path, const int loops = -1);
	static void setMusicVolume(const int volume);
	static void fadeOutMusic(const int speed = 1500);
	static void stopMusic();
};
