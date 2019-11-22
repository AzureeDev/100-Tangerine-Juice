#include "PreGame.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"

PreGame::PreGame()
{
	LilacClasses::PreGame = this;
}

void PreGame::init()
{
	OverlayManager::fadeOut(3);
	MusicManager::playMusic("assets/musics/begins.mp3");
	Globals::timer->createTimer("debugSwapToGame", 4, TimerCallbacks::getInGame, 1);
}

void PreGame::update(const float dt)
{
}
