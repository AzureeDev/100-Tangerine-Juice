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

bool AIUnit::isAI() const
{
	return true;
}
