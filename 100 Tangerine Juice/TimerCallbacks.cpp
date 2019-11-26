#include <SDL.h>
#include <vector>
#include <string>
#include "Vector2.h"
#include "Globals.h"
#include "TimerCallbacks.h"
#include "Utils.h"
#include "MusicManager.h"

using std::vector, std::string;

void TimerCallbacks::mainMenuUnitAnimation()
{
	vector<Vector2i> startPositions = {
		Vector2i(0, Utils::randBetween(128, 800)),
		Vector2i(Globals::engine->getDisplaySettings().wsWidth, Utils::randBetween(128, 800))
	};

	size_t positionPicked = rand() % startPositions.size();
	size_t randomUnitVectorId = rand() % UnitDefinitions::def.size();
	string randomUnitIdentifier = UnitDefinitions::def[randomUnitVectorId].unitId;

	LilacClasses::MainMenu->mmUnit = Unit(randomUnitIdentifier, "fwd");

	if (positionPicked == 0)
	{
		LilacClasses::MainMenu->mmUnit.setFlipped(true);
	}
	else
	{
		LilacClasses::MainMenu->mmUnit.setFlipped(false);
	}

	LilacClasses::MainMenu->mmUnit.setPosition(startPositions[positionPicked]);
	LilacClasses::MainMenu->mmUnit.setDash(true, 6);
}

void TimerCallbacks::createGame()
{
	Globals::engine->destroyClass("MainMenu");
	Globals::engine->createClass("PreGame", new PreGame);
}

void TimerCallbacks::getInGame()
{
}