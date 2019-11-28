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
	LTexture attackerDice;
	LTexture attackerDiceNumber;
	LTexture defenderDice;
	LTexture defenderDiceNumber;

	/* Battle State */
	enum class BattleState {
		PreBattle,
		AttackerTurn,
		DefenderTurn
	};

	/* Buttons */
	LButton* battleStartBtn = nullptr;
	vector<LButton*> battlePlayerSkills = {};

public:
	BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender);
	~BattleComponent();
	void init();
	void battleStart();
	void beginAttack();
	void beginDefense(int attackRoll);
	void attackOutcome(int attackRoll, int defenseRoll);
	void battleEnded();
	void hideDices();
	void update(const float dt);
};

