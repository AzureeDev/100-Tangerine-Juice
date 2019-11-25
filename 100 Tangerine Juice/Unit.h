#pragma once
#include <string>
#include "LTexture.h"
#include "Vector2.h"

using std::string;

class Unit
{
protected:
	string unitId = "";
	string unitAnimation = "std";
	string currentAnimation = "std";
	LTexture unitTexture;
	LTexture unitShadow;
	Vector2i unitPosition = { 0, 0 };
	bool unitFlipped = false;
	bool unitDashing = false;
	int unitDashMultiplier = 1;

public:
	Unit();
	Unit(const string unitIdentifier, const string defaultAnimation = "std");
	string identifier();
	LTexture& texture();
	Vector2i position();
	int x();
	int y();
	void setAnimation(const string newAnimation);
	void setDash(const bool state, const int multiplier = 1);
	void setX(const int x);
	void setY(const int y);
	void setPosition(const Vector2i pos);
	void setFlipped(const bool state);
	void placeMiddleScreen();
	virtual void render(SDL_Rect camera);
};
