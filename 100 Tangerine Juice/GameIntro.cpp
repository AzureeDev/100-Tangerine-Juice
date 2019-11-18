#include "GameIntro.h"
#include <SDL.h>

GameIntro::GameIntro() : LClass("GameIntro", this)
{
	SDL_Log("GameIntro construct");
}

void GameIntro::init()
{
	SDL_Log("GameIntro init");
	SDL_Log("I can tell my name is %s", this->getName().c_str());
}

void GameIntro::update(const float dt)
{
	SDL_Log("GameIntro update with dt: %f", dt);
}
