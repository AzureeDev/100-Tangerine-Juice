#include "Tangerine.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"
#include "Utils.h"

// Panels
#include "PanelEncounter.h"
#include "PanelBonus.h"
#include "PanelDrop.h"
#include "PanelHeal.h"
#include "PanelMove.h"
#include "PanelPower.h"
#include "AIUnit.h"

const int MAX_MAP_SIZE = 101;

Tangerine::Tangerine()
{
	LilacClasses::Tangerine = this;
}

Tangerine::~Tangerine()
{
	Globals::engine->setActiveCameraUnit(nullptr);
	Globals::timer->removeAll();
	this->units.clear();
	this->panels.clear();
}

void Tangerine::init()
{
	OverlayManager::fadeOut(3);
	MusicManager::playMusic("assets/musics/shine.mp3");

	const vector<string> uids = {
		"sora_m",
		"suguri",
		"hime",
		"saki"
	};

	world.setNewWorld("assets/worlds/ri_se_sky.png");
	world.setAllowClouds(true);
	world.setWorldColor({ 100, 100, 255, 255 });
	world.setScrollMultiplier(6);

	for (size_t i = 0; i < MAX_MAP_SIZE; ++i)
	{
		const int randomizedPanel = Utils::randBetween(0, 6);
		switch (randomizedPanel)
		{
		case 0:
			panels.push_back(make_shared<Panel>(Panel()));
			break;

		case 1:
			panels.push_back(make_shared<PanelEncounter>(PanelEncounter()));
			break;

		case 2:
			panels.push_back(make_shared<PanelBonus>(PanelBonus()));
			break;

		case 3:
			panels.push_back(make_shared<PanelDrop>(PanelDrop()));
			break;

		case 4:
			panels.push_back(make_shared<PanelHeal>(PanelHeal()));
			break;

		case 5:
			panels.push_back(make_shared<PanelMove>(PanelMove()));
			break;

		case 6:
			panels.push_back(make_shared<PanelPower>(PanelPower()));
			break;
		}

		panels[i]->setIdentifier(i);
		
		if (i == 0)
		{
			panels[i]->setPosition(
				{
					256,
					Globals::engine->getDisplaySettings().wsHeight - panels[i]->getTexture().getHeight() - 64
				}
			);
		}
		else
		{
			panels[i]->setPosition(
				{
					panels[i - 1]->getPosition().x + 184,
					Globals::engine->getDisplaySettings().wsHeight - panels[i]->getTexture().getHeight() - 64
				}
			);
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		/* The player is always the first one, so we assume it is our local player. */
		if (i == 0)
		{
			units.push_back(shared_ptr<PlayerUnit>(new PlayerUnit(uids[i])));
			units[i]->setLocalPlayerUnit();
		}
		else
		{
			/* Push the AIs */
			units.push_back(shared_ptr<AIUnit>(new AIUnit(uids[i])));
		}

		units[i]->setPlayerId(static_cast<Uint8>(i));
		const Vector2i initialPos = {
				panels[0]->getPosition().x + (panels[0]->getTexture().getWidth() / 2) - (units[i]->texture().getSheetSize() / 2),
				panels[0]->getPosition().y - 330// - (150 * static_cast<int>(i))
		};
		units[i]->setPosition(initialPos);
		units[i]->setInitialPosition(initialPos);
		units[i]->setFlipped(true);
	}

	Utils::shuffle(units);

	// Reposition of the huds on the right place
	for (size_t i = 0; i < units.size(); ++i)
	{
		units[i]->updateHudPosition(i);
		units[i]->hud()->updateHud();
	}

	units[0]->setActiveUnit();

	/* The usage of new here is being able to use lambdas with the TimerManager. */
	this->gameManager = unique_ptr<GameManager>(new GameManager(panels, units));
}

vector<shared_ptr<Panel>>& Tangerine::getMap()
{
	return this->panels;
}

unique_ptr<GameManager>& Tangerine::getGameManager()
{
	return this->gameManager;
}

void Tangerine::update(const float dt)
{
	timer += dt;
	world.render();

	this->gameManager->update(dt);

	for (size_t i = 0; i < panels.size(); ++i)
	{
		panels[i]->render(Globals::engine->getCamera());
	}

	for (size_t i = 0; i < units.size(); ++i)
	{
		/* Reverse order here to make the unit layer correct. */
		units[(units.size() - 1) - i]->render(Globals::engine->getCamera());
	}
}