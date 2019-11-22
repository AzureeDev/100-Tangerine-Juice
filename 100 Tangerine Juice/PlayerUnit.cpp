#include "PlayerUnit.h"
#include "Globals.h"

PlayerUnit::PlayerUnit()
{
}

PlayerUnit::PlayerUnit(string unitIdentifier) : Unit(unitIdentifier)
{
}

void PlayerUnit::setActiveUnit()
{
	Globals::engine->setActiveCameraUnit(this);
}

void PlayerUnit::render(SDL_Rect cameraRect)
{
	this->unitTexture.render(cameraRect);

	if (this->unitDashing)
	{
		if (this->unitFlipped)
		{
			this->setX(this->x() + (1 * this->unitDashMultiplier));
		}
		else
		{
			this->setX(this->x() - (1 * this->unitDashMultiplier));
		}
	}
}
