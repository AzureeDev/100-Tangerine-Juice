#include "PlayerUnit.h"
#include "Globals.h"
#include "Utils.h"
#include "DiceThrowComponent.h"
#include "UseSkillComponent.h"
#include "SFXManager.h"

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

	this->unitSkills = SkillDefinitions::getUnitSkills(this->identifier());

	this->hudElement = shared_ptr<HUDUnit>(new HUDUnit(this));
	this->statusMessage.setAlpha(0);
}

PlayerUnit::~PlayerUnit()
{
}

shared_ptr<HUDUnit> PlayerUnit::hud()
{
	return this->hudElement;
}

void PlayerUnit::destroyTurnButtons()
{
	this->moveBtn->disable();
	this->skillBtn->disable();
}

void PlayerUnit::activateTurnButtons()
{
	this->moveBtn->activate();
	this->skillBtn->activate();
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
	this->active = true;
}

void PlayerUnit::setInactiveUnit()
{
	this->active = false;
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

	Globals::timer->createTimer("unitExecutePanel", 0.5f, [panelId]() {
		LilacClasses::Tangerine->getMap()[panelId]->trigger();
	}, 1);
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
	}, 1);
}

bool PlayerUnit::isAI() const
{
	return false;
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
	this->moveBtn->render();
	this->skillBtn->render();

	if (this->position() != this->destinationPosition)
	{
		this->setPosition(this->initialPosition.lerp(this->destinationPosition, timer));
		this->setAnimation("fwd");
		this->currentState = UnitStates::Moving;
	}
	else if (this->position() == this->destinationPosition && !this->isKO() && this->currentState != UnitStates::CustomAnimation)
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

string PlayerUnit::getName()
{
	return UnitDefinitions::getParamsById(this->identifier()).unitName;
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

bool PlayerUnit::isActive() const
{
	return this->active;
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

void PlayerUnit::beginMovementRoll()
{
	this->destroyTurnButtons();

	if (Globals::engine->hasClass("DiceThrowComponent"))
	{
		Globals::engine->destroyClass("DiceThrowComponent");
	}

	Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(this->isAI()));
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

void PlayerUnit::removePower(const unsigned int amount)
{
	this->i_currentPower -= amount;

	if (this->i_currentPower < 0)
	{
		this->i_currentPower = 0;
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

void PlayerUnit::heal(const int amount)
{
	if (this->s_currentHealth == this->s_maxHealth)
	{
		return;
	}

	this->s_currentHealth += amount;

	if (this->s_currentHealth > this->s_maxHealth)
	{
		this->s_currentHealth = this->s_maxHealth;
	}

	SFXManager::playSFX("powerup");
	Globals::gameManager->getCurrentTurnUnit()->setStatusMessage("HEAL\n+ " + std::to_string(amount) + " HP", { 255, 128, 223, 255 });

	this->hud()->updateHud();
}

int PlayerUnit::takeDamage(const int attackRoll, const int defenseRoll, const UnitDefenseType defenseType)
{
	int damageTaken = 0;

	if (defenseType == UnitDefenseType::Defense)
	{
		damageTaken += (attackRoll - defenseRoll);

		if (damageTaken <= 1)
		{
			damageTaken = 1;
		}
	}

	this->s_currentHealth -= damageTaken;

	if (this->s_currentHealth < 0)
	{
		this->s_currentHealth = 0;
	}

	this->hud()->updateHud();

	if (this->isKO())
	{
		this->onKO();
	}

	return damageTaken;
}

void PlayerUnit::onKO()
{
	this->s_currentRecovery = this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Recovery)];

	/* Skill remove on death */
	this->unitSkills.clear();
}

int PlayerUnit::getCurrentRecovery()
{
	return this->s_currentRecovery;
}

void PlayerUnit::decreaseRecovery()
{
	this->s_currentRecovery--;
}

void PlayerUnit::revive()
{
	this->s_currentHealth = this->s_maxHealth;
	this->hud()->updateHud();
	this->setStatusMessage("REVIVED!", { 255, 255, 255, 255 });
	this->onRevived();
}

void PlayerUnit::onRevived()
{
	this->s_currentRecovery = 0;
}

void PlayerUnit::createSkillEffect(const ActiveSkill activeSkillData)
{
	for (auto& skill : this->currentSkills)
	{
		if (activeSkillData.skillIdentifier == skill.skillIdentifier)
		{
			skill.skillDuration = activeSkillData.skillDuration;
			skill.skillStack++;

			return;
		}
	}

	this->currentSkills.push_back(activeSkillData);
}

bool PlayerUnit::hasSkillEffect(const string skillIdentifier)
{
	for (auto& skill : this->currentSkills)
	{
		if (skillIdentifier == skill.skillIdentifier)
		{
			return true;
		}
	}

	return false;
}

int PlayerUnit::getCurrentStackForEffect(const string skillIdentifier)
{
	for (auto& skill : this->currentSkills)
	{
		if (skillIdentifier == skill.skillIdentifier)
		{
			return skill.skillStack;
		}
	}

	return 0;
}

void PlayerUnit::updateSkillEffect()
{
	for (size_t i = 0; i < this->currentSkills.size(); ++i)
	{
		this->currentSkills[i].skillDuration--;

		if (this->currentSkills[i].skillDuration == 0)
		{
			this->currentSkills.erase(this->currentSkills.begin() + i);
		}
	}
}

void PlayerUnit::onTurnStart()
{
	/* Skill effect on turn start */

	auto hasSkill = [this](string skillIdentifier) {
		if (this->hasSkillEffect(skillIdentifier))
		{
			return true;
		}

		return false;
	};

	if (hasSkill("hyper_fallingstars"))
	{
		int starsMin, starsMax;
		starsMin = 3 * this->getCurrentStackForEffect("hyper_fallingstars");
		starsMax = 6 * this->getCurrentStackForEffect("hyper_fallingstars");
		int starsGained = Utils::randBetween(3, 6);
		this->addStars(starsGained);
	}
}

void PlayerUnit::startTurn()
{
	SDL_Log("Player actions here");
	this->setActiveUnit();
	this->updateSkillEffect();

	if (!this->isKO())
	{
		this->onTurnStart();

		if (Globals::gameManager->getCurrentUnitParams().unitHealPerTurn)
		{
			this->heal(1);
		}

		this->moveBtn = Globals::UI->createButton("moveBtn", "assets/ui/ig/moveBtn.png");
		this->moveBtn->setPosition(
			{
				(Globals::engine->getDisplaySettings().wsWidth / 2) - (this->moveBtn->getTexture().getWidth() / 2),
				(Globals::engine->getDisplaySettings().wsHeight / 2) - (this->moveBtn->getTexture().getHeight() / 2),

			}
		);
		this->moveBtn->supplyCallback([this]() 
			{ 
				this->beginMovementRoll();
			}
		);

		this->skillBtn = Globals::UI->createButton("skillBtn", "assets/ui/ig/skillBtn.png");
		this->skillBtn->setPosition(
			{
				this->moveBtn->getX(),
				this->moveBtn->getY() + this->skillBtn->getTexture().getHeight() + 16,
				

			}
		);
		this->skillBtn->supplyCallback([this]()
			{
				Globals::engine->createClass("UseSkillComponent", new UseSkillComponent(UseSkillComponent::GameState::OutBattle));
				this->destroyTurnButtons();
			}
		);
	}
	else if (this->isKO() && this->s_currentRecovery > 1)
	{
		if (this->s_currentRecovery == 0)
		{
			this->s_currentRecovery = this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Recovery)];
		}
		else
		{
			if (Globals::engine->hasClass("DiceThrowComponent"))
			{
				Globals::engine->destroyClass("DiceThrowComponent");
			}

			Globals::engine->createClass("DiceThrowComponent", new DiceThrowComponent(this->isAI(), DiceComponentType::Recovery));
		}
	}
	else if (this->isKO() && this->s_currentRecovery <= 1)
	{
		this->revive();
		Globals::gameManager->nextTurn();
	}
}

void PlayerUnit::movement(const int diceRoll)
{
	Globals::timer->createTimer("playerUnitMovement", 0.1f, [this, diceRoll]() { this->moveByDiceNb(diceRoll); }, 1);
}

unsigned PlayerUnit::getAttackStat() const
{
	return this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Attack)] + this->s_tempStats[static_cast<int>(UnitParams::UnitStatistics::Attack)];
}

unsigned PlayerUnit::getDefenseStat() const
{
	return this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Defense)] + this->s_tempStats[static_cast<int>(UnitParams::UnitStatistics::Defense)];
}

unsigned PlayerUnit::getEvasionStat() const
{
	return this->s_stats[static_cast<int>(UnitParams::UnitStatistics::Evasion)] + this->s_tempStats[static_cast<int>(UnitParams::UnitStatistics::Evasion)];
}

vector<SkillData> PlayerUnit::getSkills() const
{
	return this->unitSkills;
}
