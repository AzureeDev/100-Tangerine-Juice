#pragma once
#include <string>
#include <map>
#include <memory>
#include "LTexture.h"
#include "Vector2.h"

using std::string, std::map, std::shared_ptr;

class Unit
{
protected:
	struct UnitCosmetics 
	{
		map<string, string> identifiers =
		{
			{ "hair", "" },
			{ "clothing", "" }
		};

		map<string, shared_ptr<LTexture>> textures = {};
	};

	string unitId = "";
	string unitAnimation = "std";
	string currentAnimation = "std";
	UnitCosmetics currentCosmetics = {};
	LTexture unitTexture;
	LTexture statusMessage;
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
	void setStatusMessage(const string message, const SDL_Color color = { 255, 255, 255, 0 });
	void setFade(const TextureFadingState state, const int mult = 1);
	void placeMiddleScreen();
	void applyCosmetic(const string cosmeticIdentifier, const string type);
	virtual void render(SDL_Rect camera);
};
