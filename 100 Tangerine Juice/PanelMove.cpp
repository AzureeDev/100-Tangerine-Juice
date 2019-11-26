#include "PanelMove.h"
#include "Globals.h"
#include "Utils.h"
#include "SFXManager.h"
#include "DiceThrowComponent.h"

PanelMove::PanelMove()
{
	panelTexture.setNewTexture("assets/panels/panel_move.png");
}

void PanelMove::trigger()
{
	Globals::timer->createTimer("movePanelEffect", .5f, []()
		{
			SFXManager::playSFX("powerup");
			if (Globals::engine->hasClass("DiceThrowComponent"))
			{
				Globals::engine->destroyClass("DiceThrowComponent");
			}

			Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(!Globals::gameManager->getCurrentTurnUnit()->isLocalUnit()));
			Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("MOVE", { 25, 255, 65, 255 });
		}, 1
	);
}