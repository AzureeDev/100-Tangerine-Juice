#include "PanelPower.h"
#include "Globals.h"
#include "SFXManager.h"

PanelPower::PanelPower()
{
	panelTexture.setNewTexture("assets/panels/panel_power.png");
}

void PanelPower::trigger()
{
	Globals::timer->createTimer("powerPanelEffect", .5f, []()
		{
			SFXManager::playSFX("powerup");
			Globals::gameManager->getCurrentTurnUnit()->addPower(1);
			Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("POWER UP!\n+1", { 223, 3, 252, 255 });
			Globals::gameManager->nextTurn();
		}, 1
	);
}