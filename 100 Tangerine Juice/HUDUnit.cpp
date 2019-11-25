#include "HUDUnit.h"
#include "Globals.h"

HUDUnit::HUDUnit()
{
}

HUDUnit::HUDUnit(PlayerUnit* unitPtr)
{
	this->unitIdentifier = unitPtr->identifier();
	this->hudTextureBg.setNewTexture("assets/units/" + this->unitIdentifier + "/_hud.png");
	this->hudHPAmount.createText("5 / 5 HP", { 235, 235, 235, 255 }, 0, Globals::resources->getFont("bleachFont"));
	this->hudStarAmount.createText("0 / 200", { 235, 235, 235, 255 }, 0, Globals::resources->getFont("bleachFont"));
	this->hudPowerAmount.createText("0 / 5", { 255, 0, 208, 255 }, 0, Globals::resources->getFont("bleachFont"));

	this->hudPowerEffect.setFixedSize(250);
	this->hudPowerEffect.setAnimationSpeed(80);
	this->hudPowerEffect.setNewTexture("assets/effects/lstrike.png");
	this->hudPowerEffect.setColor({ 174, 0, 209, 0 }, true);

	this->unitPointer = unitPtr;
}

HUDUnit::~HUDUnit()
{
	SDL_Log("HUD Destroyed");
}

void HUDUnit::setPosition(Vector2i pos)
{
	this->hudPosition = pos;
	this->hudTextureBg.setPosition(pos);
	this->hudHPAmount.setPosition(
		{
			pos.x + 335,
			pos.y + 16
		}
	);
	this->hudStarAmount.setPosition(
		{
			pos.x + 229,
			pos.y + 64
		}
	);
	this->hudPowerAmount.setPosition(
		{
			pos.x + 229,
			pos.y + 113
		}
	);

	this->hudPowerEffect.setPosition(
		{
			this->hudPowerAmount.getPosition().x + (this->hudPowerAmount.getWidth() / 2) - (this->hudPowerEffect.getSheetSize() / 2),
			this->hudPowerAmount.getPosition().y + (this->hudPowerAmount.getHeight() / 2) - (this->hudPowerEffect.getHeight() / 2),
		}
	);
}

void HUDUnit::updateHud()
{
	this->updateCurrentHP();
	this->updateCurrentStars();
	this->updateCurrentPower();
}

void HUDUnit::updateCurrentHP()
{
	string currentHP = std::to_string(this->unitPointer->getCurrentHealth());
	string maxHP = std::to_string(this->unitPointer->getMaxHealth());

	this->hudHPAmount.createText(currentHP + " / " + maxHP + " HP", { 235, 235, 235, 255 }, 0, Globals::resources->getFont("bleachFont"));
}

void HUDUnit::updateCurrentStars()
{
	string currentStars = std::to_string(this->unitPointer->getCurrentStars());

	this->hudStarAmount.createText(currentStars + " / 200", { 235, 235, 235, 255 }, 0, Globals::resources->getFont("bleachFont"));
}

void HUDUnit::updateCurrentPower()
{
	string currentPower = std::to_string(this->unitPointer->getCurrentPower());
	string maxPower = std::to_string(this->unitPointer->getMaxPower());

	this->hudPowerAmount.createText(currentPower + " / " + maxPower, { 255, 0, 208, 255 }, 0, Globals::resources->getFont("bleachFont"));
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
	this->hudPowerEffect.render();
	this->hudTextureBg.render();
	this->hudStarAmount.render();
	this->hudPowerAmount.render();
	this->hudHPAmount.render();

	this->hudPowerEffect.setAlpha(255 * this->unitPointer->getCurrentPower() / this->unitPointer->getMaxPower());

	if (!this->unitPointer->isActive())
	{
		this->hudTextureBg.setColor({ 100, 100, 100, 255 });
		this->hudStarAmount.setColor({ 100, 100, 100, 255 });
		this->hudPowerAmount.setColor({ 100, 0, 100, 255 });
		this->hudHPAmount.setColor({ 100, 100, 100, 255 });
	}
	else
	{
		this->hudTextureBg.setColor({ 255, 255, 255, 255 });
		this->hudStarAmount.setColor({ 255, 255, 255, 255 });
		this->hudPowerAmount.setColor({ 255, 0, 208, 255 });
		this->hudHPAmount.setColor({ 255, 255, 255, 255 });
	}
}