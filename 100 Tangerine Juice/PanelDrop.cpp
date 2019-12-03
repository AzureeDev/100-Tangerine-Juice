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
	if (Globals::gameManager->getCurrentTurnUnit()->getCurrentStars() == 0)
	{
		Globals::gameManager->nextTurn();
		return;
	}

	Globals::timer->createTimer("dropPanelEffect", .5f, []()
		{
			if (Globals::gameManager->getCurrentTurnUnit()->hasSkillEffect("dropbarrier"))
			{
				SFXManager::playSFX("battle_start.wav");
				Globals::gameManager->getCurrentTurnUnit()->removeSkillEffect("dropbarrier");
				Globals::gameManager->nextTurn();

				return;
			}

			const unsigned base = 3;
			const unsigned max = 10 + static_cast<unsigned>(LilacClasses::Tangerine->getGameManager()->getCurrentChapter());
			const unsigned starAmount = Utils::randBetween(base, max);
				
			SFXManager::playSFX("bad");
			Globals::gameManager->getCurrentTurnUnit()->playTempAnimation("dmg");
			Globals::gameManager->getCurrentTurnUnit()->dropStars(starAmount);
			Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("DROP...\n-" + std::to_string(starAmount), { 0, 162, 255, 255 });
			Globals::gameManager->nextTurn();
			
		}, 1
	);
}