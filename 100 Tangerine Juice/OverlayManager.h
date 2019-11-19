#pragma once
#include <SDL.h>
#include "LTexture.h"

enum class OverlayFade {
	Idle,
	FadeIn,
	FadeOut,
	FadeInOut
};

class OverlayManager
{
private:
	static LTexture overlay;
	static int fadeMultiplier;
	static OverlayFade currentFadeState;

public:
	static void init();
	static void setColor(const SDL_Color color);
	static void fadeIn(const int fadeMultiplier = 1);
	static void fadeOut(const int fadeMultiplier = 1);
	static void fadeInOut(const int fadeMultiplier = 1);
	static void hide();
	static void update(const float dt);
	static void destroy();
};
