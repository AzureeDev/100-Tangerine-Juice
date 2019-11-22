#pragma once
#include <string>
#include "LTexture.h"
#include "Vector2.h"

class Panel
{
protected:
	LTexture panelTexture;
	Vector2i panelPosition = { 0, 0 };

public:
	Panel();
	void setPosition(const Vector2i pos);
	Vector2i& getPosition();
	LTexture& getTexture();
	virtual void trigger();
	void render(const SDL_Rect camera);
};