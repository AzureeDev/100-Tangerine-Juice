#pragma once
#include <string>
#include <functional>
#include "LTexture.h"
#include "Unit.h"
#include "ButtonCallbacks.h"

using std::string;

class Unit;

class LButton
{
private:
	string buttonId;
	LTexture buttonTexture;
	LTexture buttonText;
	string buttonTextStr = "";
	SDL_Color buttonTextColor = { 255, 255, 255, 255 };
	SDL_Color buttonHighlightColor = { 255, 255, 255, 255 };
	string buttonPath;

	std::function<void(string)> buttonStrCallback = NULL;
	std::function<void()> buttonCallback = NULL;
	std::function<void(Unit*)> buttonUnitCallback = NULL;

	Unit* buttonBindedUnit = nullptr;
	string buttonBindedStr = "";
	int buttonX = 0;
	int buttonY = 0;
	int animationOriginalX = 0;
	int animationMaxButtonX = 0;
	int buttonWidth = 0;
	int buttonHeight = 0;
	bool buttonVisible = true;
	bool buttonEnabled = true;
	bool allowSound = true;
	bool playedSoundHighlight = false;
	bool allowHoverAnimation = false;

public:
	LButton();
	~LButton();
	LButton(const string id, const string btnTexturePath);
	LTexture& getTexture();
	string getId();
	void disable();
	void activate();
	bool isMouseInside();
	bool isEnabled();
	void supplyCallback(std::function<void()> clbk);
	void supplyCallback(std::function<void(string)> clbk, const string arg);
	void supplyUnitCallback(Unit* unit, std::function<void(Unit*)> clbk);
	void executeCallback();
	void event(const SDL_Event& ev);
	int getX();
	int getY();
	void setX(const int x);
	void setY(const int y);
	void setPosition(const int x, const int y);
	void setPosition(const Vector2i pos);
	void setVisible(const bool state);
	void setEnabled(const bool state);
	void setHighlightColor(const SDL_Color color);
	void setText(const string text);
	void setText(const string text, const SDL_Color color);
	void setTextColor(const SDL_Color color);
	void setAllowSound(const bool state);
	void setAllowAnimation(const bool state);

	void render();
};
