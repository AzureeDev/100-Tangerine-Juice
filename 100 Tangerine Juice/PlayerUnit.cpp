#include "PlayerUnit.h"
#include "Globals.h"
#include "Utils.h"


PlayerUnit::PlayerUnit()
{
}

PlayerUnit::PlayerUnit(string unitIdentifier) : Unit(unitIdentifier)
{
	UnitParams unitDefinition = UnitDefinitions::getParamsById(unitIdentifier);
	this->s_currentHealth = unitDefinition.unitMaxHealth;
	this->s_maxHealth = unitDefinition.unitMaxHealth;
	this->s_stats = unitDefinition.unitStats;

	this->i_currentPower = unitDefinition.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerStart)];
	this->i_maxPower = unitDefinition.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerMax)];

	this->hudElement = make_shared<HUDUnit>(HUDUnit(this));

	this->statusMessage.setAlpha(0);
}

PlayerUnit::~PlayerUnit()
{
	SDL_Log("I am destroyed.");
}

shared_ptr<HUDUnit> PlayerUnit::hud()
{
	return this->hudElement;
}

void PlayerUnit::updateHudPosition(const int id)
{
	this->hudElement->setPosition(
		{
			48 * (1 + id) + (this->hudElement->getTexture().getWidth() * id),
			32
		}
	);
}

void PlayerUnit::setInitialPosition(const Vector2i& pos)
{
	this->initialPosition = pos;
	this->destinationPosition = pos;
}

void PlayerUnit::setActiveUnit()
{
	Globals::engine->setActiveCameraUnit(this);
}

void PlayerUnit::setPlayerId(const Uint8 id)
{
	this->playerId = id;
	this->updateHudPosition(id);
}

void PlayerUnit::setLocalPlayerUnit()
{
	this->localPlayerUnit = true;
}

void PlayerUnit::setStatusMessage(const string message, const SDL_Color color)
{
	this->statusMessage.createText(message, color, 0, Globals::resources->getFont("bleachFontMedium"));
	this->statusMessage.setFade(TextureFadingState::FadeOut);
	this->statusMessage.setPosition(
		{
			this->unitTexture.getPosition().x + (this->unitTexture.getSheetSize() / 2) + 64,
			this->unitTexture.getPosition().y + (this->unitTexture.getHeight() / 2) - 96
		}
	);
}

void PlayerUnit::setCurrentState(const UnitStates state)
{
	this->currentState = state;
}

void PlayerUnit::moveTo(const Vector2i& destination)
{
	this->timer = 0.0f;
	this->initialPosition = this->position();
	this->destinationPosition = destination;
}

void PlayerUnit::moveToPanel(int panelId)
{
	if (static_cast<unsigned>(panelId) >= (LilacClasses::Tangerine->getMap().size() - 1))
	{
		// Move to the last one
		panelId = LilacClasses::Tangerine->getMap().size() - 1;
	}

	this->currentPanel = panelId;
	this->timer = 0.0f;
	this->initialPosition = this->position();
	this->destinationPosition = {
			LilacClasses::Tangerine->getMap()[panelId]->getPosition().x + (LilacClasses::Tangerine->getMap()[panelId]->getTexture().getWidth() / 2) - (this->texture().getSheetSize() / 2),
			this->position().y
	};

	Globals::timer->createTimer("unitExecutePanel", 1, [panelId]() {
		LilacClasses::Tangerine->getMap()[panelId]->trigger();
	}, 1.5f);
}

void PlayerUnit::moveByDiceNb(unsigned int diceNb)
{
	const int previousPanel = this->getUnitPanelId();
	unsigned int realMovement = diceNb;

	if (previousPanel + realMovement >= (LilacClasses::Tangerine->getMap().size() - 1))
	{
		// Move to the last one
		this->moveToPanel(LilacClasses::Tangerine->getMap().size() - 1);
		return;
	}

	this->currentPanel = previousPanel + realMovement;
	this->timer = 0.0f;
	this->initialPosition = this->position();
	this->destinationPosition = {
			LilacClasses::Tangerine->getMap()[previousPanel + realMovement]->getPosition().x + (LilacClasses::Tangerine->getMap()[previousPanel + realMovement]->getTexture().getWidth() / 2) - (this->texture().getSheetSize() / 2),
			this->position().y
	};

	Globals::timer->createTimer("unitExecutePanel", 1, [previousPanel, realMovement]() {
		LilacClasses::Tangerine->getMap()[previousPanel + realMovement]->trigger();
		}, 1.5f);
}

bool PlayerUnit::isKO() const
{
	return this->s_currentHealth <= 0;
}

void PlayerUnit::render(SDL_Rect cameraRect)
{
	this->timer += Globals::engine->GLOBAL_DELTA_TIME;

	this->unitTexture.render(cameraRect);
	this->statusMessage.render(cameraRect);
	this->hudElement->update();

	if (this->position() != this->destinationPosition)
	{
		this->setPosition(this->initialPosition.lerp(this->destinationPosition, timer));
		this->setAnimation("fwd");
		this->currentState = UnitStates::Moving;
	}
	else if(this->position() == this->destinationPosition && !this->isKO() && this->currentState != UnitStates::CustomAnimation)
	{
		this->setAnimation("std");
		this->currentState = UnitStates::Idle;
	}
	else if (this->isKO())
	{
		this->setAnimation("dmg");
		this->currentState = UnitStates::Idle;
	}

	if (this->statusMessage.getAlpha() > 0)
	{
		this->statusMessage.setPosition(
			{
				this->unitTexture.getPosition().x + (this->unitTexture.getSheetSize() / 2) + 64,
				this->statusMessage.getY() - 2
			}
		);
	}
}

int PlayerUnit::getCurrentHealth() const
{
	return this->s_currentHealth;
}

int PlayerUnit::getMaxHealth() const
{
	return this->s_maxHealth;
}

vector<int> PlayerUnit::getStats() const
{
	return this->s_stats;
}

int PlayerUnit::getCurrentStars() const
{
	return this->i_currentStars;
}

int PlayerUnit::getMaxPower() const
{
	return this->i_maxPower;
}

int PlayerUnit::getCurrentPower() const
{
	return this->i_currentPower;
}

int PlayerUnit::getUnitPanelId() const
{
	return this->currentPanel;
}

bool PlayerUnit::isLocalUnit() const
{
	return this->localPlayerUnit;
}

void PlayerUnit::playTempAnimation(const string animation, const float duration)
{
	this->currentState = UnitStates::CustomAnimation;
	this->setAnimation(animation);

	Globals::timer->createTimer(this->unitId + "_tempAnimationCancel", duration, [this]()
		{
			this->setCurrentState(UnitStates::Idle);
		}, 1
	);

}

void PlayerUnit::addPower(const unsigned int amount)
{
	this->i_currentPower += amount;

	if (this->i_currentPower >= this->i_maxPower)
	{
		this->i_currentPower = this->i_maxPower;
	}

	this->hud()->updateHud();
}

void PlayerUnit::addStars(const unsigned int amount)
{
	this->i_currentStars += amount;

	if (this->i_currentStars > 200)
	{
		this->i_currentStars = 200;
	}

	this->hud()->updateHud();
}

void PlayerUnit::dropStars(const unsigned int amount)
{
	this->i_currentStars -= amount;

	if (this->i_currentStars < 0)
	{
		this->i_currentStars = 0;
	}

	this->hud()->updateHud();
}

void PlayerUnit::startTurn()
{
	SDL_Log("Player actions here");
	this->setActiveUnit();

	Globals::timer->createTimer("startTurn", 0.5f, [this]() { this->moveByDiceNb(Utils::randBetween(1, 6)); }, 1);
}
