#include "AIUnit.h"
#include "Globals.h"
#include "Utils.h"
#include "DiceThrowComponent.h"

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

	if (Globals::engine->hasClass("DiceThrowComponent"))
	{
		Globals::engine->destroyClass("DiceThrowComponent");
	}

	Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(true));
}

bool AIUnit::isAI() const
{
	return true;
}
