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
	/* Can't gather stars ? */
	if (!UnitDefinitions::getParamsById(Globals::gameManager->getCurrentTurnUnit()->identifier()).unitCanGatherStars)
	{
		Panel::trigger();
		return;
	}

	Globals::timer->createTimer("bonusPanelEffect", .5f, []()
		{
			SFXManager::playSFX("starget");

			unsigned unitBonus = Globals::gameManager->getCurrentUnitParams().unitStarBonus;
			unsigned base = 5 + unitBonus;
			const unsigned max = 15 + static_cast<unsigned>(LilacClasses::Tangerine->getGameManager()->getCurrentChapter()) + unitBonus;
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