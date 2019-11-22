#pragma once
#include "Unit.h"
#include "HUDUnit.h"

class PlayerUnit : public Unit
{
private:
	Uint8 playerId = 0;
	HUDUnit hudElement;

public:
	PlayerUnit();
	PlayerUnit(string unitIdentifier);
	void setActiveUnit();
	virtual void render(SDL_Rect cameraRect);
	void setPlayerId(Uint8 id);
};

