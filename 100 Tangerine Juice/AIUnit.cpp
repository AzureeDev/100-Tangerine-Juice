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
	this->updateSkillEffect();

	if (!this->isKO())
	{
		if (Globals::gameManager->getCurrentUnitParams().unitHealPerTurn)
		{
			this->heal(1);
		}

		if (Globals::engine->hasClass("DiceThrowComponent"))
		{
			Globals::engine->destroyClass("DiceThrowComponent");
		}

		Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(this->isAI()));
	}
	else if (this->isKO() && this->s_currentRecovery > 1)
	{
		if (this->s_currentRecovery == 0)
		{
			this->s_currentRecovery = this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Recovery)];
		}
		else
		{
			if (Globals::engine->hasClass("DiceThrowComponent"))
			{
				Globals::engine->destroyClass("DiceThrowComponent");
			}

			Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(this->isAI(), DiceComponentType::Recovery));
		}
	}
	else if (this->isKO() && this->s_currentRecovery <= 1)
	{
		this->revive();
		Globals::gameManager->nextTurn();
	}
}

bool AIUnit::isAI() const
{
	return true;
}
