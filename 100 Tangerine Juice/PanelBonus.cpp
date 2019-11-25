#include "PanelBonus.h"
#include "SFXManager.h"
#include "Globals.h"
#include "Utils.h"

PanelBonus::PanelBonus()
{
	panelTexture.setNewTexture("assets/panels/panel_bonus.png");
}

void PanelBonus::trigger()
{
	Globals::timer->createTimer("powerPanelEffect", .5f, []()
		{
			SFXManager::playSFX("starget");

			const unsigned base = 15;
			const unsigned max = 30 + static_cast<unsigned>(LilacClasses::Tangerine->getGameManager()->getCurrentChapter());
			const unsigned starAmount = Utils::randBetween(base, max);

			Globals::gameManager->getCurrentTurnUnit()->addStars(starAmount);
			Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("STARS\n+" + std::to_string(starAmount), { 255, 230, 0, 255 });

			if (Globals::gameManager->getCurrentTurnUnit()->getCurrentStars() >= 200)
			{
				Globals::gameManager->gameEnded();
			}
			else
			{
				Globals::gameManager->nextTurn();
			}
		}, 1
	);
}