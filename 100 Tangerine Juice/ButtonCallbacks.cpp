#include "ButtonCallbacks.h"
#include "Globals.h"
#include "Utils.h"
#include "OverlayManager.h"
#include "MusicManager.h"

void ButtonCallbacks::proceedToMainMenu()
{
	Globals::engine->destroyClass("GameIntro");
	Globals::engine->createClass("MainMenu", new MainMenu);
}

void ButtonCallbacks::quitGame()
{
	Globals::engine->exit();
}

void ButtonCallbacks::mainMenuCredits()
{
	LilacClasses::MainMenu->clearButtons();
	LilacClasses::MainMenu->setHeaderTitle("CREDITS");
	LilacClasses::MainMenu->createCreditsButtons();
}

void ButtonCallbacks::mainMenuUnitDB()
{
	LilacClasses::MainMenu->clearButtons();
	LilacClasses::MainMenu->setHeaderTitle("UNIT DATABASE");
	LilacClasses::MainMenu->createUnitDBButtons();
}

void ButtonCallbacks::unitDBRequestInfo(const string unitIdentifier)
{
	Globals::engine->destroyClass("unitCardComponent");

	UnitParams params = UnitDefinitions::getParamsById(unitIdentifier);
	LilacClasses::MainMenu->setHeaderTitle(Utils::strToUpper(params.unitName));

	Globals::engine->createClass("unitCardComponent", new UnitCardComponent(params));
}

void ButtonCallbacks::backToMainMenu()
{
	Globals::engine->destroyClass("unitCardComponent");

	LilacClasses::MainMenu->clearButtons();
	LilacClasses::MainMenu->setHeaderTitle("MAIN MENU");
	LilacClasses::MainMenu->createMainMenuButtons();
	LilacClasses::MainMenu->hideHelpPicture();
}

void ButtonCallbacks::openLink(const string link)
{
	Utils::openBrowserLink(link);
}

void ButtonCallbacks::startGame()
{
	LilacClasses::MainMenu->clearButtons();
	OverlayManager::fadeIn(3);
	MusicManager::fadeOutMusic();

	Globals::timer->createTimer("ingameState", 3, TimerCallbacks::createGame, 1);
}