#include "PanelDrop.h"
#include "Globals.h"
#include "Utils.h"
#include "SFXManager.h"

PanelDrop::PanelDrop()
{
	panelTexture.setNewTexture("assets/panels/panel_drop.png");
}

void PanelDrop::trigger()
{
	Globals::timer->createTimer("powerPanelEffect", .5f, []()
		{
			SFXManager::playSFX("bad");

			if (Globals::gameManager->getCurrentTurnUnit()->getCurrentStars() == 0)
			{
				Globals::gameManager->nextTurn();
			}
			else
			{
				const unsigned base = 10;
				const unsigned max = 20 + static_cast<unsigned>(LilacClasses::Tangerine->getGameManager()->getCurrentChapter());
				const unsigned starAmount = Utils::randBetween(base, max);

				Globals::gameManager->getCurrentTurnUnit()->playTempAnimation("dmg");
				Globals::gameManager->getCurrentTurnUnit()->dropStars(starAmount);
				Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("DROP...\n-" + std::to_string(starAmount), { 0, 162, 255, 255 });
				Globals::gameManager->nextTurn();
			}
		}, 1
	);
}