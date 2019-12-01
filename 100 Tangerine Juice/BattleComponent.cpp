#include "BattleComponent.h"
#include "Globals.h"
#include "Utils.h"
#include "SFXManager.h"
#include "UseSkillComponent.h"

const auto colorStat = [](const int statistic) {
	if (statistic < 0)
	{
		return SDL_Color({ 255, 125, 125, 255 });
	}

	return SDL_Color({ 255, 255, 255, 255 });
};

BattleComponent::BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender)
{
	this->battleAttacker = attacker.get();
	this->battleDefender = defender.get();
	Globals::currentBattleInstance = this;
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

	if (this->battleSkillBtn != nullptr)
	{
		Globals::UI->destroyButton("battleSkillBtn");
		this->battleSkillBtn = nullptr;
	}

	if (this->battleDefendBtn != nullptr)
	{
		Globals::UI->destroyButton("battleDefendBtn");
		this->battleDefendBtn = nullptr;
	}

	if (this->battleEvasionBtn != nullptr)
	{
		Globals::UI->destroyButton("battleEvasionBtn");
		this->battleEvasionBtn = nullptr;
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
	this->componentStatBg.setNewTexture("assets/ui/rect_base.png");
	this->componentStatBg.setColor({ 10, 10, 10, 235 }, true);
	this->componentStatBg.setSize(Globals::engine->getDisplaySettings().wsWidth, 64);
	this->componentStatBg.setPosition({ 0, this->componentBgContour.bottom().y });
	this->componentIcon.setNewTexture("assets/ui/ig/battleIcon.png");
	this->componentIcon.placeMiddleScreen();
	this->componentIcon.setY(this->componentBgContour.getY() - (this->componentIcon.getHeight() / 2));

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

	this->createUnitStats();

	if (!this->battleAttacker->isAI() || !this->battleDefender->isAI())
	{
		this->battleStartBtn = Globals::UI->createButton("battleStart", "assets/ui/ig/battleStartBtn.png");
		this->battleStartBtn->getTexture().setColor({ 150, 150, 150, 255 }, true);
		this->battleStartBtn->setHighlightColor({ 255, 255, 255, 255 });
		this->battleStartBtn->supplyCallback([this]() 
			{ 
				this->setButtonVisibility(false);

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

		this->battleSkillBtn = Globals::UI->createButton("battleSkillBtn", "assets/ui/ig/skillBtn.png");
		this->battleSkillBtn->getTexture().setColor({ 150, 150, 150, 255 }, true);
		this->battleSkillBtn->setHighlightColor({ 255, 255, 255, 255 });

		this->battleSkillBtn->supplyCallback([this]()
			{
				this->setButtonVisibility(false);
				Globals::engine->createClass("UseSkillComponent", new UseSkillComponent(UseSkillComponent::GameState::InBattle));
			}
		);

		this->battleSkillBtn->setPosition(
			{
				this->battleStartBtn->getX(),
				this->battleStartBtn->getY() + this->battleStartBtn->getTexture().getHeight() + 16
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

void BattleComponent::setButtonVisibility(const bool enabled)
{
	if (enabled)
	{
		this->battleStartBtn->activate();
		this->battleSkillBtn->activate();
	}
	else
	{
		this->battleStartBtn->disable();
		this->battleSkillBtn->disable();
	}
}

void BattleComponent::createUnitStats()
{
	/* Definition */
	shared_ptr<LTexture> healthBg = shared_ptr<LTexture>(new LTexture("assets/ui/battle/healthBg.png"));
	shared_ptr<LTexture> healthBg2 = shared_ptr<LTexture>(new LTexture("assets/ui/battle/healthBg.png"));
	shared_ptr<LTexture> attackIcon = shared_ptr<LTexture>(new LTexture("assets/ui/stats/attack.png"));
	shared_ptr<LTexture> attackIcon2 = shared_ptr<LTexture>(new LTexture("assets/ui/stats/attack.png"));
	shared_ptr<LTexture> defenseIcon = shared_ptr<LTexture>(new LTexture("assets/ui/stats/defense.png"));
	shared_ptr<LTexture> defenseIcon2 = shared_ptr<LTexture>(new LTexture("assets/ui/stats/defense.png"));
	shared_ptr<LTexture> evasionIcon = shared_ptr<LTexture>(new LTexture("assets/ui/stats/evasion.png"));
	shared_ptr<LTexture> evasionIcon2 = shared_ptr<LTexture>(new LTexture("assets/ui/stats/evasion.png"));

	shared_ptr<LTexture> attackerCurrentHealth = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> attackerMaxHealth = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> attackerAttack = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> attackerDefense = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> attackerEvasion = shared_ptr<LTexture>(new LTexture);

	shared_ptr<LTexture> defenderCurrentHealth = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> defenderMaxHealth = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> defenderAttack = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> defenderDefense = shared_ptr<LTexture>(new LTexture);
	shared_ptr<LTexture> defenderEvasion = shared_ptr<LTexture>(new LTexture);

	attackerCurrentHealth->createText(std::to_string(this->battleAttacker->getCurrentHealth()), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	attackerMaxHealth->createText(std::to_string(this->battleAttacker->getMaxHealth()), { 220, 220, 220, 255 }, 0, Globals::resources->getFont("defaultFont"));
	attackerAttack->createText(std::to_string(this->battleAttacker->getAttackStat()), colorStat(this->battleAttacker->getAttackStat()), 0, Globals::resources->getFont("defaultFont36"));
	attackerDefense->createText(std::to_string(this->battleAttacker->getDefenseStat()), colorStat(this->battleAttacker->getDefenseStat()), 0, Globals::resources->getFont("defaultFont36"));
	attackerEvasion->createText(std::to_string(this->battleAttacker->getEvasionStat()), colorStat(this->battleAttacker->getEvasionStat()), 0, Globals::resources->getFont("defaultFont36"));

	defenderCurrentHealth->createText(std::to_string(this->battleDefender->getCurrentHealth()), { 235, 235, 235, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	defenderMaxHealth->createText(std::to_string(this->battleDefender->getMaxHealth()), { 235, 235, 235, 255 }, 0, Globals::resources->getFont("defaultFont"));
	defenderAttack->createText(std::to_string(this->battleDefender->getAttackStat()), colorStat(this->battleDefender->getAttackStat()), 0, Globals::resources->getFont("defaultFont36"));
	defenderDefense->createText(std::to_string(this->battleDefender->getDefenseStat()), colorStat(this->battleDefender->getDefenseStat()), 0, Globals::resources->getFont("defaultFont36"));
	defenderEvasion->createText(std::to_string(this->battleDefender->getEvasionStat()), colorStat(this->battleDefender->getEvasionStat()), 0, Globals::resources->getFont("defaultFont36"));

	/* Position */
	healthBg->setPosition({ this->battleAttackerUnit.position().x - healthBg->getWidth() + 68, this->battleAttackerUnit.position().y + this->battleAttackerUnit.texture().getHeight() - (healthBg->getHeight() * 2) });
	attackerCurrentHealth->setPosition({ healthBg->getX() + 60 - attackerCurrentHealth->getWidth() / 2, healthBg->getY() + 60 - attackerCurrentHealth->getHeight() / 2 });
	attackerMaxHealth->setPosition({ healthBg->getX() + 121 - attackerMaxHealth->getWidth() / 2, healthBg->getY() + 84 - attackerMaxHealth->getHeight() / 2 });
	attackIcon->setPosition({ this->battleAttackerUnit.position().x + 128, this->componentStatBg.getPosition().y + (this->componentStatBg.getHeight() / 2) - (attackIcon->getHeight() / 2) });
	attackerAttack->setPosition({ attackIcon->getX() + attackIcon->getWidth() + 8, attackIcon->getY() });
	defenseIcon->setPosition({ this->battleAttackerUnit.position().x + (this->battleAttackerUnit.texture().getSheetSize() / 2) - defenseIcon->getWidth(), attackIcon->getY() });
	attackerDefense->setPosition({ defenseIcon->getX() + defenseIcon->getWidth() + 8, defenseIcon->getY() });
	evasionIcon->setPosition({ this->battleAttackerUnit.position().x + (this->battleAttackerUnit.texture().getSheetSize()) - 192, attackIcon->getY() });
	attackerEvasion->setPosition({ evasionIcon->getX() + evasionIcon->getWidth() + 8, evasionIcon->getY() });

	healthBg2->setPosition({ this->battleDefenderUnit.position().x + this->battleDefenderUnit.texture().getSheetSize() - 92, this->battleDefenderUnit.position().y + this->battleDefenderUnit.texture().getHeight() - (healthBg2->getHeight() * 2) });
	defenderCurrentHealth->setPosition({ healthBg2->getX() + 60 - defenderCurrentHealth->getWidth() / 2, healthBg2->getY() + 60 - defenderCurrentHealth->getHeight() / 2 });
	defenderMaxHealth->setPosition({ healthBg2->getX() + 121 - defenderMaxHealth->getWidth() / 2, healthBg2->getY() + 84 - defenderMaxHealth->getHeight() / 2 });
	attackIcon2->setPosition({ this->battleDefenderUnit.position().x + 128, this->componentStatBg.getPosition().y + (this->componentStatBg.getHeight() / 2) - (attackIcon->getHeight() / 2) });
	defenderAttack->setPosition({ attackIcon2->getX() + attackIcon2->getWidth() + 8, attackIcon2->getY() });
	defenseIcon2->setPosition({ this->battleDefenderUnit.position().x + (this->battleDefenderUnit.texture().getSheetSize() / 2) - defenseIcon->getWidth(), attackIcon->getY() });
	defenderDefense->setPosition({ defenseIcon2->getX() + defenseIcon2->getWidth() + 8, defenseIcon2->getY() });
	evasionIcon2->setPosition({ this->battleDefenderUnit.position().x + (this->battleDefenderUnit.texture().getSheetSize()) - 192, attackIcon->getY() });
	defenderEvasion->setPosition({ evasionIcon2->getX() + evasionIcon2->getWidth() + 8, evasionIcon2->getY() });

	/* Insertion */
	this->attackerStats = {
		healthBg,
		attackerCurrentHealth,
		attackerMaxHealth,
		attackIcon,
		attackerAttack,
		defenseIcon,
		attackerDefense,
		evasionIcon,
		attackerEvasion
	};

	this->defenderStats = {
		healthBg2,
		defenderCurrentHealth,
		defenderMaxHealth,
		attackIcon2,
		defenderAttack,
		defenseIcon2,
		defenderDefense,
		evasionIcon2,
		defenderEvasion
	};
}

void BattleComponent::updateUnitStats()
{
	/* Update on stat change, or damage taken */
	const int attackerAttack = this->battleAttacker->getAttackStat();
	const int attackerDefense = this->battleAttacker->getDefenseStat();
	const int attackerEvasion = this->battleAttacker->getEvasionStat();
	const int attackerCurrentHP = this->battleAttacker->getCurrentHealth();

	const int defenderAttack = this->battleDefender->getAttackStat();
	const int defenderDefense = this->battleDefender->getDefenseStat();
	const int defenderEvasion = this->battleDefender->getEvasionStat();
	const int defenderCurrentHP = this->battleDefender->getCurrentHealth();

	this->attackerStats[static_cast<int>(UnitVectorStat::Attack)]->createText(std::to_string(attackerAttack), colorStat(attackerAttack), 0, Globals::resources->getFont("defaultFont36"));
	this->attackerStats[static_cast<int>(UnitVectorStat::Defense)]->createText(std::to_string(attackerDefense), colorStat(attackerDefense), 0, Globals::resources->getFont("defaultFont36"));
	this->attackerStats[static_cast<int>(UnitVectorStat::Evasion)]->createText(std::to_string(attackerEvasion), colorStat(attackerEvasion), 0, Globals::resources->getFont("defaultFont36"));
	this->attackerStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->createText(std::to_string(attackerCurrentHP), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));

	this->defenderStats[static_cast<int>(UnitVectorStat::Attack)]->createText(std::to_string(defenderAttack), colorStat(defenderAttack), 0, Globals::resources->getFont("defaultFont36"));
	this->defenderStats[static_cast<int>(UnitVectorStat::Defense)]->createText(std::to_string(defenderDefense), colorStat(defenderDefense), 0, Globals::resources->getFont("defaultFont36"));
	this->defenderStats[static_cast<int>(UnitVectorStat::Evasion)]->createText(std::to_string(defenderEvasion), colorStat(defenderEvasion), 0, Globals::resources->getFont("defaultFont36"));
	this->defenderStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->createText(std::to_string(defenderCurrentHP), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));

	/* Little reposition for the health only as it's position is on the middle */
	this->attackerStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->setPosition(
		{ 
			this->attackerStats[static_cast<int>(UnitVectorStat::HealthBackground)]->getX() + 60 - this->attackerStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->getWidth() / 2,
			this->attackerStats[static_cast<int>(UnitVectorStat::HealthBackground)]->getY() + 60 - this->attackerStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->getHeight() / 2
		}
	);

	this->defenderStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->setPosition(
		{
			this->defenderStats[static_cast<int>(UnitVectorStat::HealthBackground)]->getX() + 60 - this->defenderStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->getWidth() / 2,
			this->defenderStats[static_cast<int>(UnitVectorStat::HealthBackground)]->getY() + 60 - this->defenderStats[static_cast<int>(UnitVectorStat::CurrentHealth)]->getHeight() / 2
		}
	);
}

void BattleComponent::battleStart()
{
	this->updateUnitStats();
	this->beginAttack();
}

void BattleComponent::beginAttack()
{
	PlayerUnit* damageDealer = this->currentTurn % 2 == 0 ? this->battleAttacker : this->battleDefender;
	PlayerUnit* defender = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& damageDealerUnit = this->currentTurn % 2 == 0 ? this->battleAttackerUnit : this->battleDefenderUnit;
	Unit& defenderUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
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

	if (defender->isAI())
	{
		this->aiDecideAction(attackRoll);
	}
	else
	{
		this->battleDefendBtn = Globals::UI->createButton("battleDefendBtn", "assets/ui/battle/defend.png");
		this->battleEvasionBtn = Globals::UI->createButton("battleEvasionBtn", "assets/ui/battle/evade.png");

		this->battleDefendBtn->setPosition(
			{
				defenderUnit.position().x + (defenderUnit.texture().getSheetSize() / 2) - (this->battleDefendBtn->getTexture().getWidth() / 2) - 128,
				defenderUnit.position().y + 64,
			}
		);

		this->battleEvasionBtn->setPosition(
			{
				defenderUnit.position().x + (defenderUnit.texture().getSheetSize() / 2) - (this->battleEvasionBtn->getTexture().getWidth() / 2) + 128,
				defenderUnit.position().y + 64,
			}
		);

		this->battleDefendBtn->supplyCallback([this, attackRoll]()
			{
				this->battleDefendBtn->disable();
				this->battleEvasionBtn->disable();

				Globals::timer->createTimer("delayPlayerAction", 0.5f, [this, attackRoll]() { this->beginDefense(attackRoll); }, 1);
			}
		);

		this->battleEvasionBtn->supplyCallback([this, attackRoll]()
			{
				this->battleDefendBtn->disable();
				this->battleEvasionBtn->disable();

				Globals::timer->createTimer("delayPlayerAction", 0.5f, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
			}
		);
	}
}

void BattleComponent::beginDefense(int attackRoll)
{
	PlayerUnit* defender = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& defenderUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
	LTexture& defenderDice = this->currentTurn % 2 == 0 ? this->defenderDice : this->attackerDice;
	LTexture& defenderDiceNumber = this->currentTurn % 2 == 0 ? this->defenderDiceNumber : this->attackerDiceNumber;

	defenderUnit.setAnimation("aggressive");
	defenderUnit.setStatusMessage("DEFENDING", { 175, 255, 175, 255 });
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

void BattleComponent::beginEvasion(int attackRoll)
{
	PlayerUnit* defender = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& defenderUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
	LTexture& defenderDice = this->currentTurn % 2 == 0 ? this->defenderDice : this->attackerDice;
	LTexture& defenderDiceNumber = this->currentTurn % 2 == 0 ? this->defenderDiceNumber : this->attackerDiceNumber;

	defenderUnit.setAnimation("aggressive");
	defenderUnit.setStatusMessage("EVADING", { 175, 175, 255, 255 });
	SFXManager::playSFX("attack");

	int defenderRoll = Utils::randBetween(1, 6);
	defenderDice.setNewTexture("assets/dice/" + std::to_string(defenderRoll) + ".png");
	defenderRoll += defender->getEvasionStat();
	defenderRoll = defenderRoll < 1 ? 1 : defenderRoll;

	defenderDiceNumber.createText(std::to_string(defenderRoll), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	defenderDiceNumber.setPosition(
		{
			defenderDice.getX() + (defenderDice.getWidth() / 2) - (defenderDiceNumber.getWidth() / 2),
			defenderDice.top().y - 64
		}
	);

	SDL_Log("Defender eva: %d", defenderRoll);

	Globals::timer->createTimer("delayOutcome", 1, [this, attackRoll, defenderRoll]() { this->attackOutcome(attackRoll, defenderRoll, true); }, 1);
}

void BattleComponent::aiDecideAction(int attackRoll)
{
	PlayerUnit* defender = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	int currentEvasion = defender->getEvasionStat();

	if (attackRoll == 1)
	{
		Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
		return;
	}

	if (defender->getCurrentHealth() == 1)
	{
		Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
		return;
	}

	if (attackRoll < currentEvasion)
	{
		Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
		return;
	}

	if (rand() % 100 < 50)
	{
		if (attackRoll <= currentEvasion)
		{
			Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
			return;
		}
	}

	if (rand() % 100 < 75)
	{
		if (attackRoll - currentEvasion < 3)
		{
			Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginEvasion(attackRoll); }, 1);
			return;
		}
	}

	Globals::timer->createTimer("delayAIAction", 1, [this, attackRoll]() { this->beginDefense(attackRoll); }, 1);
}

void BattleComponent::attackOutcome(int attackRoll, int defenseRoll, bool isEvasion)
{
	PlayerUnit* damageTaker = this->currentTurn % 2 == 0 ? this->battleDefender : this->battleAttacker;
	Unit& damageTakerUnit = this->currentTurn % 2 == 0 ? this->battleDefenderUnit : this->battleAttackerUnit;
	PlayerUnit::UnitDefenseType defenseType = isEvasion ? PlayerUnit::UnitDefenseType::Evasion : PlayerUnit::UnitDefenseType::Defense;

	int dmgAmount = damageTaker->takeDamage(attackRoll, defenseRoll, defenseType);
	this->updateUnitStats();

	if (dmgAmount > 0)
	{
		if (dmgAmount >= 3)
		{
			SFXManager::playSFX("dmg");
		}
		else
		{
			SFXManager::playSFX("dmg_light");
		}
		
		damageTakerUnit.setAnimation("dmg");
		damageTakerUnit.setStatusMessage("DAMAGE\n- " + std::to_string(dmgAmount) + " HP", { 25, 0, 0, 255 });
	}
	else
	{
		SFXManager::playSFX("evade");
		damageTakerUnit.setAnimation("std");
		damageTakerUnit.setStatusMessage("EVADED", { 175, 175, 255, 255 });
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
	this->componentStatBg.render();

	for (const auto& ltexture : this->attackerStats)
	{
		ltexture->render();
	}

	for (const auto& ltexture : this->defenderStats)
	{
		ltexture->render();
	}

	this->componentIcon.render();
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

	if (this->battleSkillBtn != nullptr)
	{
		this->battleSkillBtn->render();
	}

	if (this->battleEvasionBtn != nullptr)
	{
		this->battleEvasionBtn->render();
	}

	if (this->battleDefendBtn != nullptr)
	{
		this->battleDefendBtn->render();
	}
}