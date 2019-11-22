#include "HUDUnit.h"

HUDUnit::HUDUnit()
{
}

HUDUnit::HUDUnit(Unit* unitPtr)
{
	this->unitIdentifier = unitPtr->identifier();
	hudTextureBg.setNewTexture("assets/units/" + this->unitIdentifier + "/_hud.png");
}

void HUDUnit::setPosition(Vector2i pos)
{
	this->hudPosition = pos;
	this->hudTextureBg.setPosition(pos);
}

Vector2i& HUDUnit::getPosition()
{
	return this->hudPosition;
}

LTexture& HUDUnit::getTexture()
{
	return this->hudTextureBg;
}

void HUDUnit::update()
{
	hudTextureBg.render();
}
