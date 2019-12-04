#include "EndgameComponent.h"
#include "Globals.h"
#include "Utils.h"
#include "OverlayManager.h"
#include <algorithm>

struct PlayerStatSort {
	// Predicate: Sort by star amount and panel progression
	bool operator()(PlayerItem a, PlayerItem b) {
		return a.playerPtr->getCurrentStars() + (a.playerPtr->getUnitPanelId() * 2) > b.playerPtr->getCurrentStars() + (b.playerPtr->getUnitPanelId() * 2);
	}
};

EndgameComponent::EndgameComponent()
{
}

EndgameComponent::~EndgameComponent()
{
	Globals::UI->destroyButton("exitComponentBtn");
}

void EndgameComponent::init()
{
	Globals::gameManager->disableButtons();

	/* Background */
	componentBg.setNewTexture("assets/ui/ig/endFade.png");
	componentBg.setFade(TextureFadingState::FadeIn);

	/* Winner label */
	componentWinnerLabel.createText("Winner:", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	componentWinnerLabel.placeMiddleScreen();
	componentWinnerLabel.setY(componentWinnerLabel.getY() - (140 * 3));
	componentWinnerLabel.setFade(TextureFadingState::FadeIn);

	/* Fill units in vector */
	for (const auto& unit : Globals::gameManager->getUnits())
	{
		playerItems.push_back({ Unit(unit->identifier()), unit, {} });
	}

	/* Sort them */
	std::sort(playerItems.begin(), playerItems.end(), PlayerStatSort());

	/* Winner name label */
	winnerName.createText(Utils::strToUpper(playerItems[0].playerPtr->getName()), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontExLarge"));
	winnerName.placeMiddleScreen();
	winnerName.setY(componentWinnerLabel.bottom().y + 16);
	winnerName.setFade(TextureFadingState::FadeIn);

	componentExitLabel.createText("Click anywhere to continue", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	componentExitLabel.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - componentExitLabel.getWidth() - 10,
			Globals::engine->getDisplaySettings().wsHeight - componentExitLabel.getHeight() - 10
		}
	);

	componentExitBtn = Globals::UI->createButton("exitComponentBtn");
	componentExitBtn->setAllowSound(false);
	componentExitBtn->getTexture().setSize(Globals::engine->getDisplaySettings().wsWidth, Globals::engine->getDisplaySettings().wsHeight);
	componentExitBtn->supplyCallback([this]() { this->onExitPressed(); });
	componentExitBtn->setEnabled(false);

	/* Create the player items for stats */
	Globals::timer->createTimer("delayShowingUnits", 2.f, [this]()
		{
			this->createPlayerItems();
		}, 1
	);
}

void EndgameComponent::createPlayerItems()
{
	const vector<SDL_Color> rankColor = {
		SDL_Color({255, 215, 0, 255}),
		SDL_Color({192, 192, 192, 255}),
		SDL_Color({205, 127, 50, 255}),
		SDL_Color({95, 95, 95, 255}),
	};

	for (size_t i = 0; i < playerItems.size(); ++i)
	{
		playerItems[i].playerUnit.setFlipped(true);

		if (i == 0)
		{
			/* Main position */
			playerItems[i].playerUnit.setPosition(
				{
					componentWinnerLabel.getX() - playerItems[i].playerUnit.texture().getSheetSize() - 160,
					winnerName.bottom().y - 128
				}
			);
		}
		else
		{
			playerItems[i].playerUnit.setPosition(
				{
					playerItems[i - 1].playerUnit.x() - 64,
					playerItems[i - 1].playerUnit.texture().getY() + playerItems[i - 1].playerUnit.texture().getHeight() - (115 * 3)
				}
			);
		}

		/* Name & Stats */
		shared_ptr<LTexture> unitName = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> unitStarAmountIcon = shared_ptr<LTexture>(new LTexture("assets/ui/ig/starEndscreen.png"));
		shared_ptr<LTexture> unitPanelProgressIcon = shared_ptr<LTexture>(new LTexture("assets/ui/ig/panelEndscreen.png"));
		shared_ptr<LTexture> unitStarAmount = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> unitPanelProgress = shared_ptr<LTexture>(new LTexture);

		unitName->createText(playerItems[i].playerPtr->getName(), rankColor[i], 0, Globals::resources->getFont("defaultFont32"));
		unitName->setPosition(
			{
				playerItems[i].playerUnit.position().x + playerItems[i].playerUnit.texture().getSheetSize() - 128,
				playerItems[i].playerUnit.position().y + 166
			}
		);

		unitPanelProgressIcon->setPosition(
			{
				unitName->getX(),
				unitName->bottom().y + 32
			}
		);

		unitPanelProgress->createText(std::to_string(playerItems[i].playerPtr->getUnitPanelId()) + " / " + std::to_string(LilacClasses::Tangerine->getMapSize() - 1));
		unitPanelProgress->setPosition(
			{
				unitPanelProgressIcon->right() + 8,
				unitPanelProgressIcon->getY() + (unitPanelProgressIcon->getHeight() / 2) - (unitPanelProgress->getHeight() / 2)
			}
		);

		unitStarAmountIcon->setPosition(
			{
				unitPanelProgressIcon->right() + 128,
				unitPanelProgressIcon->getY()
			}
		);

		unitStarAmount->createText(std::to_string(playerItems[i].playerPtr->getCurrentStars()) + " / 200");
		unitStarAmount->setPosition(
			{
				unitStarAmountIcon->right() + 8,
				unitStarAmountIcon->getY() + (unitStarAmountIcon->getHeight() / 2) - (unitStarAmount->getHeight() / 2)
			}
		);

		playerItems[i].itemTextures = { unitName, unitPanelProgress, unitStarAmount, unitPanelProgressIcon, unitStarAmountIcon  };

		if (i == playerItems.size() - 1)
		{
			playerItems[i].playerUnit.setAnimation("dmg");
		}

		playerItems[i].playerUnit.texture().setFade(TextureFadingState::FadeIn, 3);
	}

	this->allowRenderUnits = true;
	componentExitLabel.setFade(TextureFadingState::FadeIn);
	componentExitBtn->setEnabled(true);
}

void EndgameComponent::onExitPressed()
{
	componentExitBtn->setEnabled(false);
	OverlayManager::fadeIn(6);

	Globals::timer->createTimer("delaySwapState", 2, []() 
		{
			Globals::engine->createClass("MainMenu", new MainMenu);
			Globals::engine->destroyClass("Tangerine");
			Globals::engine->destroyClass("EndgameComponent");
		}, 1
	);
}

void EndgameComponent::update(const float dt)
{
	componentBg.render();
	componentWinnerLabel.render();
	winnerName.render();

	if (this->allowRenderUnits)
	{
		for (auto& playerItem : this->playerItems)
		{
			playerItem.playerUnit.render({});

			for (auto& playerItemTexture : playerItem.itemTextures)
			{
				playerItemTexture->render();
			}
		}

		componentExitLabel.render();
		componentExitBtn->render();
	}
}
