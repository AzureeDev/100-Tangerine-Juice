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

float timer = 0.0f;

Tangerine::Tangerine()
{
	LilacClasses::Tangerine = this;
}

Tangerine::~Tangerine()
{
	Globals::engine->setActiveCameraUnit(nullptr);
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

	/*
	test = PlayerUnit("sora_m");
	test.setAnimation("fwd");
	test.texture().placeLeftScreen();
	test.setFlipped(true);
	test.setDash(true, 9);
	test.setActiveUnit();*/

	world.setNewWorld("assets/worlds/ml_sky.png");
	world.setScrollMultiplier(6);

	for (size_t i = 0; i < 100; ++i)
	{
		const int randomizedPanel = Utils::randBetween(0, 6);
		switch (randomizedPanel)
		{
		case 0:
			panels.push_back(make_unique<Panel>(Panel()));
			break;

		case 1:
			panels.push_back(make_unique<PanelEncounter>(PanelEncounter()));
			break;

		case 2:
			panels.push_back(make_unique<PanelBonus>(PanelBonus()));
			break;

		case 3:
			panels.push_back(make_unique<PanelDrop>(PanelDrop()));
			break;

		case 4:
			panels.push_back(make_unique<PanelHeal>(PanelHeal()));
			break;

		case 5:
			panels.push_back(make_unique<PanelMove>(PanelMove()));
			break;

		case 6:
			panels.push_back(make_unique<PanelPower>(PanelPower()));
			break;
		}
		
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
					panels[i - 1]->getPosition().x + 256,
					Globals::engine->getDisplaySettings().wsHeight - panels[i]->getTexture().getHeight() - 64
				}
			);
		}
	}

	for (size_t i = 0; i < 4; ++i)
	{
		units.push_back(make_unique<PlayerUnit>(PlayerUnit(uids[i])));
		units[i]->setPlayerId(static_cast<Uint8>(i));
		units[i]->setPosition(
			{
				panels[0]->getPosition().x + (panels[0]->getTexture().getWidth() / 2) - (units[i]->texture().getSheetSize() / 2),
				panels[0]->getPosition().y - 384 - (150 * static_cast<int>(i))
			}
		);
		units[i]->setFlipped(true);
	}
}

void Tangerine::update(const float dt)
{
	timer += dt;
	world.render();

	for (size_t i = 0; i < panels.size(); ++i)
	{
		panels[i]->render(Globals::engine->getCamera());
	}

	for (size_t i = 0; i < units.size(); ++i)
	{
		/* Reverse order here to make the unit layer correct. */
		units[(units.size() - 1) - i]->render(Globals::engine->getCamera());
	}

	test.render(Globals::engine->getCamera());
}