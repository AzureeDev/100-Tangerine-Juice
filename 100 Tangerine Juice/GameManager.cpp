#include "GameManager.h"
#include "Globals.h"
#include "SFXManager.h"
#include "MusicManager.h"

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

	this->restart = Globals::UI->createButton("restart_game_debug");
	this->restart->supplyCallback([]() {
		GameParams params = LilacClasses::Tangerine->getGameParams();
		Globals::engine->destroyClass("Tangerine");
		Globals::engine->createClass("Tangerine", new Tangerine(params));
	});
	this->restart->getTexture().createText("RESTART");
	this->restart->setPosition({ 5, Globals::engine->getDisplaySettings().wsHeight - this->restart->getTexture().getHeight() });

	this->initGame();
}

GameManager::~GameManager()
{
	Globals::UI->destroyButton("restart_game_debug");
}

void GameManager::initGame()
{
	this->currentChapter++;

	SFXManager::playSFX("new_chapter");
	this->createHudMessage("Beginning of Chapter 1");
	this->callback("gameBegin", [this]() { this->nextTurn(); }, 2);
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

shared_ptr<PlayerUnit> GameManager::getCurrentTurnUnit()
{
	if (this->currentPlayerTurn >= 0 && static_cast<unsigned int>(this->currentPlayerTurn) < this->units.size())
	{
		return this->units[this->currentPlayerTurn];
	}

	SDL_Log("GameManager::getCurrentTurnUnit() - Tried to get an ID out of the vector bounds: %d . Return unit 0", this->currentPlayerTurn);

	return this->units[0];
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

void GameManager::nextTurn()
{
	if (this->isStandingOnPanel(this->map.size() - 1))
	{
		this->gameEnded();
		return;
	}

	float delay = 0.5f;

	if (static_cast<unsigned int>(this->currentPlayerTurn) >= this->units.size())
	{
		delay = 1.f;
	}

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

	/*
		Game ending code here...
	*/
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

void GameManager::update(const float dt)
{
	this->messageBg.render();
	this->messageText.render();
	this->restart->render();
}