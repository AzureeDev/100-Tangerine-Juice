#include "AIUnit.h"
#include "Globals.h"
#include "Utils.h"

AIUnit::AIUnit()
{
}

AIUnit::AIUnit(string identifier) : PlayerUnit(identifier)
{
	SDL_Log("AI created: %s", identifier.c_str());
}

void AIUnit::startTurn()
{
	SDL_Log("AI action here");

	// Perform move
	this->setActiveUnit();
	Globals::timer->createTimer("startTurn", 0.5f, [this]() { this->moveByDiceNb(Utils::randBetween(1, 6)); }, 1);
}