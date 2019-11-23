#pragma once
#include <string>
#include "LClass.h"
#include "PlayerUnit.h"

using std::string;

class PlayerUnit;

class HUDUnit
{
private:
	string unitIdentifier = "";
	PlayerUnit* unitPointer = nullptr;
	LTexture hudTextureBg;
	LTexture hudHPAmount;
	LTexture hudStarAmount;
	LTexture hudPowerAmount;
	Vector2i hudPosition = { 0, 0 };

public:
	HUDUnit();
	HUDUnit(PlayerUnit* unitPtr);
	void setPosition(Vector2i pos);
	void updateHud();
	void updateCurrentHP();
	void updateCurrentStars();
	void updateCurrentPower();
	Vector2i& getPosition();
	LTexture& getTexture();
	void update();
};

