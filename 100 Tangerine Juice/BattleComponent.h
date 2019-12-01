#pragma once
#include "LClass.h"
#include "PlayerUnit.h"
#include "LButton.h"
#include <memory>
#include <vector>

using std::shared_ptr, std::vector;

class BattleComponent : public LClass
{
private:
	/* Core variables */
	int maxTurns = 2;
	int currentTurn = 0;

	/* Determine if they're AIs, to make them do actions automatically. */
	bool battleAIAttacker = false;
	bool battleAIDefender = false;

	/* Pointers to the shared_ptr, I suppose it's better that way rather adding a count to the original one... Besides, clearing these is easy enough. */
	PlayerUnit* battleAttacker = nullptr;
	PlayerUnit* battleDefender = nullptr;

	/* Regular Units for the rendering of the sprites. */
	Unit battleAttackerUnit;
	Unit battleDefenderUnit;

	/* LTextures */
	LTexture componentBgContour;
	LTexture componentBg;
	LTexture componentStatBg;
	LTexture componentIcon;
	LTexture attackerDice;
	LTexture attackerDiceNumber;
	LTexture defenderDice;
	LTexture defenderDiceNumber;

	/* Unit statistics rendering */
	vector<shared_ptr<LTexture>> attackerStats = {};
	vector<shared_ptr<LTexture>> defenderStats = {};

	/* Battle State */
	enum class BattleState {
		PreBattle,
		AttackerTurn,
		DefenderTurn
	};

	/* Buttons */
	LButton* battleStartBtn = nullptr;
	LButton* battleSkillBtn = nullptr;
	LButton* battleDefendBtn = nullptr;
	LButton* battleEvasionBtn = nullptr;

	/* Enum for the component text */
	enum class UnitVectorStat
	{
		HealthBackground = 0,
		CurrentHealth = 1,
		MaxHealth = 2,
		Attack = 4,
		Defense = 6,
		Evasion = 8
	};

public:
	BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender);
	~BattleComponent();
	void init();
	void setButtonVisibility(const bool enabled);
	void createUnitStats();
	void updateUnitStats();
	void battleStart();
	void beginAttack();
	void beginDefense(int attackRoll);
	void beginEvasion(int attackRoll);
	void aiDecideAction(int attackRoll);
	void attackOutcome(int attackRoll, int defenseRoll, bool isEvasion = false);
	void battleEnded();
	void hideDices();
	void update(const float dt);
};

