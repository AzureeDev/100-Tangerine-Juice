#include "PanelMove.h"
#include "Globals.h"
#include "Utils.h"
#include "SFXManager.h"

PanelMove::PanelMove()
{
	panelTexture.setNewTexture("assets/panels/panel_move.png");
}

void PanelMove::trigger()
{
	Globals::timer->createTimer("movePanelEffect", .5f, []() 
		{
			SFXManager::playSFX("powerup");
			Globals::gameManager->getCurrentTurnUnit()->moveByDiceNb(Utils::randBetween(1, 6)); 
			Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("MOVE", { 25, 255, 65, 255 });
		}, 1
	);
}