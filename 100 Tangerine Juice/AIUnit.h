#pragma once
#include "PlayerUnit.h"
class AIUnit : public PlayerUnit
{
public:
	AIUnit();
	AIUnit(string identifier);
	virtual bool isAI() const;
};
