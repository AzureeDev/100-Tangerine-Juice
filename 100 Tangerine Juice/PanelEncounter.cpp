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
	Globals::timer->createTimer("powerPanelEffect", .5f, []()
		{
			SFXManager::playSFX("powerup");

			Globals::engine->createClass("BattleComponent", 
				new BattleComponent(
					Globals::gameManager->getCurrentTurnUnit(), 
					Globals::gameManager->getRandomUnitExcluding(Globals::gameManager->getCurrentTurnUnit())
				));
		}, 1
	);
}