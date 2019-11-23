#include "PlayerUnit.h"
#include "Globals.h"


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

void PlayerUnit::moveTo(const Vector2i& destination)
{
	this->timer = 0.0f;
	this->initialPosition = this->position();
	this->destinationPosition = destination;
}

void PlayerUnit::moveToPanel(const int panelId)
{
	this->timer = 0.0f;
	this->initialPosition = this->position();
	this->destinationPosition = {
			LilacClasses::Tangerine->getMap()[panelId]->getPosition().x + (LilacClasses::Tangerine->getMap()[5]->getTexture().getWidth() / 2) - (this->texture().getSheetSize() / 2),
			this->position().y
	};
}

bool PlayerUnit::isKO() const
{
	return this->s_currentHealth <= 0;
}

void PlayerUnit::render(SDL_Rect cameraRect)
{
	this->timer += Globals::engine->GLOBAL_DELTA_TIME;

	this->unitTexture.render(cameraRect);
	this->hudElement->update();

	if (this->position() != this->destinationPosition)
	{
		this->setPosition(this->initialPosition.lerp(this->destinationPosition, timer / 6));
		this->setAnimation("fwd");
		this->currentState = UnitStates::Moving;
	}
	else if(this->position() == this->destinationPosition && !this->isKO())
	{
		this->setAnimation("std");
		this->currentState = UnitStates::Idle;
	}
	else if (this->isKO())
	{
		this->setAnimation("dmg");
		this->currentState = UnitStates::Idle;
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
