#include "OverlayManager.h"
#include "Globals.h"
#include "LTimer.h"

/*
	OverlayManager - Manages a global texture fading black to transparent or the other way around.

	This is on top of everything, including the mouse.
*/

LTexture OverlayManager::overlay;
int OverlayManager::fadeMultiplier = 1;
OverlayFade OverlayManager::currentFadeState = OverlayFade::Idle;

void OverlayManager::init()
{
	OverlayManager::overlay.setNewTexture("assets/ui/overlay.png");
	OverlayManager::overlay.setColor({ 0, 0, 0, 0 });
	OverlayManager::overlay.setSize(Globals::engine->getDisplaySettings().wsWidth, Globals::engine->getDisplaySettings().wsHeight);
}

void OverlayManager::setColor(const SDL_Color color)
{
	OverlayManager::overlay.setColor(color);
}

void OverlayManager::fadeIn(const int fadeMultiplier)
{
	OverlayManager::overlay.setAlpha(0);
	OverlayManager::fadeMultiplier = fadeMultiplier;
	OverlayManager::currentFadeState = OverlayFade::FadeIn;
}

void OverlayManager::fadeOut(const int fadeMultiplier)
{
	OverlayManager::overlay.setAlpha(255);
	OverlayManager::fadeMultiplier = fadeMultiplier;
	OverlayManager::currentFadeState = OverlayFade::FadeOut;
}

void OverlayManager::fadeInOut(const int fadeMultiplier)
{
	OverlayManager::overlay.setAlpha(0);
	OverlayManager::fadeMultiplier = fadeMultiplier;
	OverlayManager::currentFadeState = OverlayFade::FadeInOut;
}

void OverlayManager::hide()
{
	OverlayManager::currentFadeState = OverlayFade::Idle;
	OverlayManager::overlay.setAlpha(0);
}

void OverlayManager::update(const float dt)
{
	switch (OverlayManager::currentFadeState)
	{
	case OverlayFade::FadeIn:
		OverlayManager::overlay.setAlpha(OverlayManager::overlay.getAlpha() + (1 * OverlayManager::fadeMultiplier));

		if (OverlayManager::overlay.getAlpha() == 255)
		{
			OverlayManager::currentFadeState = OverlayFade::Idle;
		}
		break;

	case OverlayFade::FadeOut:
		OverlayManager::overlay.setAlpha(OverlayManager::overlay.getAlpha() - (1 * OverlayManager::fadeMultiplier));

		if (OverlayManager::overlay.getAlpha() == 0)
		{
			OverlayManager::currentFadeState = OverlayFade::Idle;
		}
		break;

	case OverlayFade::FadeInOut:
		OverlayManager::overlay.setAlpha(OverlayManager::overlay.getAlpha() + (1 * OverlayManager::fadeMultiplier));

		if (OverlayManager::overlay.getAlpha() == 255)
		{
			OverlayManager::currentFadeState = OverlayFade::FadeOut;
		}
		break;
	}

	OverlayManager::overlay.render();
}

void OverlayManager::destroy()
{
	OverlayManager::overlay.destroy();
}