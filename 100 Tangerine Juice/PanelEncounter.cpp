#include "PanelEncounter.h"
#include "Globals.h"
#include "SFXManager.h"
#include "BattleComponent.h"

PanelEncounter::PanelEncounter()
{
	panelTexture.setNewTexture("assets/panels/panel_battle.png");
}

void PanelEncounter::trigger()
{
	if (Globals::gameManager->getAliveUnitsCount() > 1)
	{
		Globals::timer->createTimer("powerPanelEffect", .5f, []()
			{
				SFXManager::playSFX("powerup");

				if (Globals::engine->hasClass("BattleComponent"))
				{
					Globals::engine->destroyClass("BattleComponent");
				}

				Globals::engine->createClass("BattleComponent",
					new BattleComponent(
						Globals::gameManager->getCurrentTurnUnit(),
						Globals::gameManager->getRandomAliveUnitExcluding(Globals::gameManager->getCurrentTurnUnit())
					));
			}, 1
		);
	}
	else
	{
		Panel::trigger();
	}
}