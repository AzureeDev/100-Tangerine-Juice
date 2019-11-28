#include "PanelHeal.h"
#include "Globals.h"
#include "SFXManager.h"

PanelHeal::PanelHeal()
{
	panelTexture.setNewTexture("assets/panels/panel_heal.png");
}

void PanelHeal::trigger()
{
	if (Globals::gameManager->getCurrentTurnUnit()->getCurrentHealth() == Globals::gameManager->getCurrentTurnUnit()->getMaxHealth())
	{
		Panel::trigger();
	}
	else
	{
		Globals::timer->createTimer("healPanelEffect", .5f, []()
			{
				Globals::gameManager->getCurrentTurnUnit()->heal(1);
				Globals::gameManager->nextTurn();
			}, 1
		);
	}
}