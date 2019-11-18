#pragma once
#include <string>
#include "LTexture.h"
#include "Vector2.h"

using std::string;

class Unit
{
private:
	string unitId = "";
	string unitAnimation = "std";
	LTexture unitTexture;
	Vector2i unitPosition = { 0, 0 };

public:
	Unit();
	Unit(const string unitIdentifier, const string defaultAnimation = "std");
	LTexture& texture();
	void setPosition(const Vector2i pos);
	void placeMiddleScreen();
	void render();
};

