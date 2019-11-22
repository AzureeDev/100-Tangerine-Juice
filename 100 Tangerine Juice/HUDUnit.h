#pragma once
#include <string>
#include "LClass.h"
#include "Unit.h"

using std::string;

class HUDUnit
{
private:
	string unitIdentifier = "";
	LTexture hudTextureBg;
	Vector2i hudPosition = { 0, 0 };

public:
	HUDUnit();
	HUDUnit(Unit* unitPtr);
	void setPosition(Vector2i pos);
	Vector2i& getPosition();
	LTexture& getTexture();
	void update();
};

