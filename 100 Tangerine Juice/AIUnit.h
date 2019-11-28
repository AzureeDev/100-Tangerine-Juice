#pragma once
#include "PlayerUnit.h"
class AIUnit : public PlayerUnit
{
public:
	AIUnit();
	AIUnit(string identifier);
	virtual void startTurn();
	virtual bool isAI() const;
};
