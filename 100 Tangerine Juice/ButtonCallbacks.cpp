#include "ButtonCallbacks.h"
#include "Globals.h"

void ButtonCallbacks::proceedToMainMenu()
{
	Globals::engine->destroyClass("GameIntro");
	Globals::engine->createClass("MainMenu", new MainMenu);
}

void ButtonCallbacks::quitGame()
{
	Globals::engine->exit();
}