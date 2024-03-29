#include "GameManager.h"
#include "Globals.h"
#include "SFXManager.h"
#include "MusicManager.h"
#include "Utils.h"
#include "Discord.h"
#include "PreGame.h"
#include "EndgameComponent.h"

void GameManager::callback(const string id, const function<void()> clbk, const float timer, const int repeat)
{
	Globals::timer->createTimer(id, timer, clbk, repeat);
}

void GameManager::removeCallback(const string id)
{
	Globals::timer->removeTimer(id);
}

GameManager::GameManager(Map& map, Players& units)
{
	Globals::gameManager = this;

	this->map = map;
	this->units = units;

	this->messageBg.setNewTexture("assets/ui/rect_base.png");
	this->messageBg.setPosition(
		{
			0,
			this->units[0]->hud()->getTexture().bottom().y + 32
		}
	);
	this->messageBg.setColor({ 0, 0, 0, 125 }, true);
	this->messageBg.setSize(Globals::engine->getDisplaySettings().wsWidth, 32 * 2);

	this->mainMenu = Globals::UI->createButton("back_main_menu");
	this->mainMenu->supplyCallback([]()
		{
			Globals::engine->createClass("MainMenu", new MainMenu);
			Globals::engine->destroyClass("Tangerine");
		}
	);
	this->mainMenu->getTexture().createText("MAIN MENU");
	this->mainMenu->setPosition({ 5, Globals::engine->getDisplaySettings().wsHeight - this->mainMenu->getTexture().getHeight() });

	this->restart = Globals::UI->createButton("restart_game_debug");
	this->restart->supplyCallback([]() {
		GameParams params = LilacClasses::Tangerine->getGameParams();
		Globals::engine->destroyClass("Tangerine");
		Globals::engine->createClass("Tangerine", new Tangerine(params));
	});
	this->restart->getTexture().createText("RESTART");
	this->restart->setPosition({ this->mainMenu->getX() + this->mainMenu->getTexture().getWidth() + 32, Globals::engine->getDisplaySettings().wsHeight - this->restart->getTexture().getHeight() });

	string worldGenPresence = "";
	string worldGenPresenceText = "";
	
	switch (LilacClasses::Tangerine->getGameParams().pickedGeneration)
	{
	case GameParams::WorldGeneration::TotalRandom:
		worldGenPresence = "totalrandom";
		worldGenPresenceText = "Total Random Generation";
		break;

	case GameParams::WorldGeneration::FairRandom:
		worldGenPresence = "fairrandom";
		worldGenPresenceText = "Fair Random Generation";
		break;

	case GameParams::WorldGeneration::Battlefield:
		worldGenPresence = "battlefield";
		worldGenPresenceText = "Battlefield Generation";
		break;
	}

	Discord::setRichPresence(
		{
			"Playing",
			"",
			this->getLocalUnit()->identifier(),
			"Playing as " + this->getLocalUnit()->getName(),
			worldGenPresence,
			worldGenPresenceText
		}
	);

	this->initGame();
}

GameManager::~GameManager()
{
	Globals::UI->destroyButton("restart_game_debug");
	Globals::UI->destroyButton("back_main_menu");
}

void GameManager::initGame()
{
	this->currentChapter++;

	SFXManager::playSFX("new_chapter");
	this->createHudMessage("Beginning of Chapter 1");
	this->callback("gameBegin", [this]() { this->nextTurn(); }, 2);
}

void GameManager::disableButtons()
{
	this->mainMenu->disable();
	this->restart->disable();
}

void GameManager::createHudMessage(const string msg, const float duration)
{
	this->messageBg.setFade(TextureFadingState::FadeIn);
	this->messageText.setFade(TextureFadingState::FadeIn);

	this->messageText.createText(msg, { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFont32"));
	this->messageText.setPosition(
		{
			(this->messageBg.getWidth() / 2) - (this->messageText.getWidth() / 2),
			this->messageBg.getY() + (this->messageBg.getHeight() / 2) - (this->messageText.getHeight() / 2)
		}
	);

	this->callback("destroyHudMessage", [this]() {
		this->messageBg.setFade(TextureFadingState::FadeOut);
		this->messageText.destroyText();
		}, duration);
}

vector<shared_ptr<PlayerUnit>> GameManager::getUnits()
{
	return this->units;
}

shared_ptr<PlayerUnit> GameManager::getCurrentTurnUnit()
{
	if (this->currentPlayerTurn >= 0 && static_cast<unsigned int>(this->currentPlayerTurn) < this->units.size())
	{
		return this->units[this->currentPlayerTurn];
	}

	SDL_Log("GameManager::getCurrentTurnUnit() - Tried to get an ID out of the vector bounds: %d . Return unit 0", this->currentPlayerTurn);

	return this->units[0];
}

shared_ptr<PlayerUnit> GameManager::getRandomUnitExcluding(const shared_ptr<PlayerUnit> exclusion)
{
	const string excludedUnitIdentifier = exclusion->identifier();
	vector<shared_ptr<PlayerUnit>> shuffledUnits = this->units;
	Utils::shuffle(shuffledUnits);

	while (true)
	{
		for (auto& unit : shuffledUnits)
		{
			if (unit->identifier() != excludedUnitIdentifier)
			{
				return unit;
			}
		}
	}

	SDL_Log("GameManager::getRandomUnitExcluding : Something went awfully wrong...");

	return nullptr;
}

shared_ptr<PlayerUnit> GameManager::getRandomAliveUnitExcluding(const shared_ptr<PlayerUnit> exclusion)
{
	const string excludedUnitIdentifier = exclusion->identifier();
	vector<shared_ptr<PlayerUnit>> shuffledUnits = this->units;
	Utils::shuffle(shuffledUnits);

	while (true)
	{
		for (auto& unit : shuffledUnits)
		{
			if (!unit->hasSkillEffect("stealth"))
			{
				if (unit->identifier() != excludedUnitIdentifier && !unit->isKO())
				{
					return unit;
				}
			}
		}
	}

	SDL_Log("GameManager::getRandomUnitExcluding : Something went awfully wrong...");

	return nullptr;
}

UnitParams GameManager::getCurrentUnitParams()
{
	return UnitDefinitions::getParamsById(this->getCurrentTurnUnit()->identifier());
}

int GameManager::getCurrentChapter() const
{
	return this->currentChapter;
}

shared_ptr<PlayerUnit> GameManager::getLocalUnit()
{
	for (size_t i = 0; i < this->units.size(); ++i)
	{
		if (this->units[i]->isLocalUnit())
		{
			return this->units[i];
		}
	}

	SDL_Log("GameManager::getLocalUnit() - No local unit defined! Assuming the player is the ID 0 then...");

	return this->units[0];
}

shared_ptr<PlayerUnit> GameManager::getUnitByIdentifier(const string identifier)
{
	for (const auto& unit : this->units)
	{
		if (unit->identifier() == identifier)
		{
			return unit;
		}
	}

	SDL_Log("GameManager::getUnitByIdentifier - Couldn't find any unit with the identifier %s", identifier.c_str());
	return nullptr;
}

unsigned GameManager::getAliveUnitsCount() const
{
	unsigned amount = 0;

	for (const auto& unit : this->units)
	{
		// Stealth Mode count as a fake death
		if (!unit->isKO() && !unit->hasSkillEffect("stealth"))
		{
			amount++;
		}
	}

	return amount;
}

void GameManager::nextTurn()
{
	Discord::setState("Currently Playing");
	Discord::setDetails(std::to_string(this->getLocalUnit()->getUnitPanelId()) + " / " + std::to_string(LilacClasses::Tangerine->getMapSize()) + " Panels" + " | " + std::to_string(this->getLocalUnit()->getCurrentStars()) + " / 200 Stars");

	if (this->isStandingOnPanel(this->map.size() - 1))
	{
		this->gameEnded();
		return;
	}

	float delay = 1.f;

	this->callback("startChapter", [this]() {
		// Old unit
		this->getCurrentTurnUnit()->setInactiveUnit();

		this->currentPlayerTurn++;

		if (static_cast<unsigned int>(this->currentPlayerTurn) >= this->units.size())
		{
			SDL_Log("New chapter");
			this->currentPlayerTurn = 0;
			this->currentChapter++;
			this->createHudMessage("Beginning of Chapter " + std::to_string(this->currentChapter));
			SFXManager::playSFX("new_chapter");
		}

		SDL_Log("Now the turn of %s", this->getCurrentTurnUnit()->identifier().c_str());
		SFXManager::playSFX("new_turn");

		// New unit
		this->getCurrentTurnUnit()->startTurn();
		}, delay);
}

void GameManager::gameEnded()
{
	MusicManager::fadeOutMusic(1000);
	SFXManager::playSFX("victory");

	/*this->endingFade.setNewTexture("assets/ui/ig/endFade.png");
	this->endingFade.setFade(TextureFadingState::FadeIn);*/

	/*
		Game ending code here...
	*/

	Globals::engine->createClass("EndgameComponent", new EndgameComponent);
}

bool GameManager::isStandingOnPanel(const int panelId) const
{
	for (const auto& unit : this->units)
	{
		if (unit->getUnitPanelId() == panelId)
		{
			return true;
		}
	}

	return false;
}

void GameManager::useSkill(const string skillIdentifier)
{
	SFXManager::playSFX("skill_activation");
	this->getCurrentTurnUnit()->playTempAnimation("aggressive", 2.f);
	this->createHudMessage(this->getCurrentTurnUnit()->getName() + " is using the skill " + SkillDefinitions::getSkillData(skillIdentifier).skillName);

	/* Executing the skill */
	Globals::timer->createTimer("delayExecuteSkill", 2.0f, [this, skillIdentifier]() 
		{
			SFXManager::playSFX("powerup");
			this->getCurrentTurnUnit()->removePower(SkillDefinitions::getSkillData(skillIdentifier).skillCost);
			SkillDefinitions::getSkillData(skillIdentifier).skillCallback(this->getCurrentTurnUnit()); 
		}, 1
	);

	Globals::timer->createTimer("delayPostSkill", 3.0f, [this]() { this->getCurrentTurnUnit()->beginMovementRoll(); }, 1);
}

void GameManager::update(const float dt)
{
	this->messageBg.render();
	this->messageText.render();
	this->restart->render();
	this->mainMenu->render();
	this->endingFade.render();
}