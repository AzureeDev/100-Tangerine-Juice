#include "BattleComponent.h"
#include "Globals.h"
#include "Utils.h"
#include "SFXManager.h"

BattleComponent::BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender)
{
	this->battleAttacker = attacker.get();
	this->battleDefender = defender.get();
}

BattleComponent::~BattleComponent()
{
	this->battleAttacker = nullptr;
	this->battleDefender = nullptr;

	if (this->battleStartBtn != nullptr)
	{
		Globals::UI->destroyButton("battleStart");
		this->battleStartBtn = nullptr;
	}
}

void BattleComponent::init()
{
	SDL_Log("Initiate battle between %s and %s", battleAttacker->identifier().c_str(), battleDefender->identifier().c_str());

	this->componentBgContour.setNewTexture("assets/ui/rect_base.png");
	this->componentBgContour.setColor({ 10, 10, 10, 255 }, true);
	this->componentBgContour.setSize(Globals::engine->getDisplaySettings().wsWidth, 310);
	this->componentBgContour.placeMiddleScreen();
	this->componentBg.setNewTexture("assets/ui/rect_gradient_base.png");
	this->componentBg.setColor({ 200, 0, 0, 255 }, true);
	this->componentBg.setSize(Globals::engine->getDisplaySettings().wsWidth, 300);
	this->componentBg.placeMiddleScreen();

	this->battleAttackerUnit = Unit(this->battleAttacker->identifier());
	this->battleDefenderUnit = Unit(this->battleDefender->identifier());

	this->battleAttackerUnit.placeMiddleScreen();
	this->battleAttackerUnit.setFlipped(true);
	this->battleAttackerUnit.setX(this->battleAttackerUnit.texture().getX() - 128 * 3);

	this->battleDefenderUnit.placeMiddleScreen();
	this->battleDefenderUnit.setX(this->battleDefenderUnit.texture().getX() + 128 * 3);

	this->attackerDice.placeMiddleScreen();
	this->attackerDice.setX(this->attackerDice.getX() - 88 * 3);
	this->attackerDice.setY(this->attackerDice.getY() + 64);
	this->defenderDice.placeMiddleScreen();
	this->defenderDice.setX(this->defenderDice.getX() + 64 * 3);
	this->defenderDice.setY(this->defenderDice.getY() + 64);

	if (!this->battleAttacker->isAI() || !this->battleDefender->isAI())
	{
		this->battleStartBtn = Globals::UI->createButton("battleStart", "assets/ui/ig/battleStartBtn.png");
		this->battleStartBtn->getTexture().setColor({ 150, 150, 150, 255 }, true);
		this->battleStartBtn->setHighlightColor({ 255, 255, 255, 255 });
		this->battleStartBtn->supplyCallback([this]() 
			{ 
				this->battleStartBtn->setEnabled(false);
				this->battleStartBtn->setVisible(false);

				Globals::timer->createTimer("battleStartShortDelay", 0.5f, [this]() 
					{
						this->battleStart(); 
					}, 1
				);
			}
		);

		this->battleStartBtn->setPosition(
			{
				(Globals::engine->getDisplaySettings().wsWidth / 2 - this->battleStartBtn->getTexture().getWidth() / 2),
				(Globals::engine->getDisplaySettings().wsHeight / 2 - this->battleStartBtn->getTexture().getHeight() / 2) - 64
			}
		);
	}
	else
	{
		/* Create chance of skill use or not here */
		Globals::timer->createTimer("battleStartShortDelay", 1.f, [this]()
			{
				this->battleStart();
			}, 1
		);
	}
}

void BattleComponent::battleStart()
{
	this->beginAttack();
}

void BattleComponent::beginAttack()
{
	PlayerUnit* damageDealer = this->currentTurn % 2 == 0 ? this->battleAttacker : this->battleDefender ;
	Unit& damageDealerUnit = this->currentTurn % 2 == 0 ? this->battleAttackerUnit : this->battleDefenderUnit;
	LTexture& damageDealerDice = this->currentTurn % 2 == 0 ? this->attackerDice : this->defenderDice;
	LTexture& damageDealerDiceNumber = this->currentTurn % 2 == 0 ? this->attackerDiceNumber : this->defenderDiceNumber;

	damageDealerUnit.setAnimation("aggressive");
	SFXManager::playSFX("attack");

	int attackRoll = Utils::randBetween(1, 6);
	damageDealerDice.setNewTexture("assets/dice/" + std::to_string(attackRoll) + ".png");
	attackRoll += damageDealer->getAttackStat();
	attackRoll = attackRoll < 1 ? 1 : attackRoll;

	damageDealerDiceNumber.createText(std::to_string(attackRoll), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	damageDealerDiceNumber.setPosition(
		{
			damageDealerDice.getX() + (damageDealerDice.getWidth() / 2) - (damageDealerDiceNumber.getWidth() / 2),
			damageDealerDice.top().y - 64
		}
	);

	SDL_Log("Attacker atk: %d", attackRoll);

	/* If AI, decide auto, or else put the buttons over there, if the defender is the player. */
	Globals::timer->createTimer("delayDefense", 1, [this, attackRoll]() { this->beginDefense(attackRoll); }, 1);
}

void BattleComponent::beginDefense(int attackRoll)
{
	PlayerUnit* defender = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& defenderUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
	LTexture& defenderDice = this->currentTurn % 2 == 0 ? this->defenderDice : this->attackerDice;
	LTexture& defenderDiceNumber = this->currentTurn % 2 == 0 ? this->defenderDiceNumber : this->attackerDiceNumber;

	defenderUnit.setAnimation("aggressive");
	SFXManager::playSFX("attack");

	int defenderRoll = Utils::randBetween(1, 6);
	defenderDice.setNewTexture("assets/dice/" + std::to_string(defenderRoll) + ".png");
	defenderRoll += defender->getDefenseStat();
	defenderRoll = defenderRoll < 1 ? 1 : defenderRoll;

	defenderDiceNumber.createText(std::to_string(defenderRoll), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	defenderDiceNumber.setPosition(
		{
			defenderDice.getX() + (defenderDice.getWidth() / 2) - (defenderDiceNumber.getWidth() / 2),
			defenderDice.top().y - 64
		}
	);

	SDL_Log("Defender def: %d", defenderRoll);

	Globals::timer->createTimer("delayOutcome", 1, [this, attackRoll, defenderRoll]() { this->attackOutcome(attackRoll, defenderRoll); }, 1);
}

void BattleComponent::attackOutcome(int attackRoll, int defenseRoll)
{
	PlayerUnit* damageTaker = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& damageTakerUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
	int dmgAmount = damageTaker->takeDamage(attackRoll, defenseRoll, PlayerUnit::UnitDefenseType::Defense);

	if (dmgAmount > 0)
	{
		SFXManager::playSFX("dmg");
		damageTakerUnit.setAnimation("dmg");
		damageTakerUnit.setStatusMessage("DAMAGE TAKEN\n- " + std::to_string(dmgAmount) + " HP");
	}

	if (!damageTaker->isKO())
	{
		Globals::timer->createTimer("delayPostDamage", 0.5f, [this]() 
			{ 
				this->hideDices();
				this->battleAttackerUnit.setAnimation("std");
				this->battleDefenderUnit.setAnimation("std");
			}, 1
		);
		
		this->currentTurn++;

		Globals::timer->createTimer("delayNextTurn", 0.75f, [this]() 
			{
				if (this->currentTurn >= this->maxTurns)
				{
					this->battleEnded();
				}
				else
				{
					this->beginAttack();
				}
			}, 1
		);
	}
	else
	{
		Globals::timer->createTimer("delayEndBattle", 0.75f, [this]() { this->battleEnded(); }, 1);
	}
}

void BattleComponent::battleEnded()
{
	Globals::engine->destroyClass("BattleComponent");
	Globals::gameManager->nextTurn();
}

void BattleComponent::hideDices()
{
	this->attackerDice.setNewTexture("assets/ui/transparent.png");
	this->defenderDice.setNewTexture("assets/ui/transparent.png");

	this->attackerDiceNumber.destroyText();
	this->defenderDiceNumber.destroyText();
}

void BattleComponent::update(const float dt)
{
	this->componentBgContour.render();
	this->componentBg.render();
	this->battleAttackerUnit.render({});
	this->battleDefenderUnit.render({});

	this->attackerDice.render();
	this->defenderDice.render();
	this->attackerDiceNumber.render();
	this->defenderDiceNumber.render();

	if (this->battleStartBtn != nullptr)
	{
		this->battleStartBtn->render();
	}
}
