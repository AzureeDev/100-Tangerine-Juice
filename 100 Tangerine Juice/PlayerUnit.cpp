#include "PlayerUnit.h"
#include "Globals.h"

PlayerUnit::PlayerUnit()
{
}

PlayerUnit::PlayerUnit(string unitIdentifier) : Unit(unitIdentifier)
{
	this->hudElement = HUDUnit(this);
}

void PlayerUnit::setActiveUnit()
{
	Globals::engine->setActiveCameraUnit(this);
}

void PlayerUnit::render(SDL_Rect cameraRect)
{
	this->unitTexture.render(cameraRect);
	this->hudElement.update();

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

void PlayerUnit::setPlayerId(Uint8 id)
{
	this->playerId = id;
	this->hudElement.setPosition(
		{
			48 * (1 + id) + (this->hudElement.getTexture().getWidth() * id),
			32
		}
	);
}
