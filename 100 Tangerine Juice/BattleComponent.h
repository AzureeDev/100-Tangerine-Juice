#pragma once
#include "LClass.h"
#include "PlayerUnit.h"
#include <memory>

using std::shared_ptr;

class BattleComponent : public LClass
{
private:
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

	/* Battle State */
	enum class BattleState {
		PreBattle,
		AttackerTurn,
		DefenderTurn
	};

public:
	BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender);
	~BattleComponent();
	void init();
	void battleEnded();
	void update(const float dt);
};

