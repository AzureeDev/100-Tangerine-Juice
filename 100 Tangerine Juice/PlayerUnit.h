#pragma once
#include "Unit.h"
class PlayerUnit : public Unit
{
public:
	PlayerUnit();
	PlayerUnit(string unitIdentifier);
	void setActiveUnit();
	virtual void render(SDL_Rect cameraRect);
};

