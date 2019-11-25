#include "World.h"
#include "Globals.h"

/*
	World

	Handles the infinite scrolling background.
*/

World::World()
{
}

World::World(const string worldTexture)
{
	this->worldTexture = Globals::resources->createTexture(worldTexture);
	this->cloudTexture = Globals::resources->createTexture("assets/worlds/add_clouds.png");
}

SDL_Color World::getWorldColor()
{
	return this->worldColor;
}

void World::setNewWorld(const string path)
{
	this->worldTexture = Globals::resources->createTexture(path);
	this->cloudTexture = Globals::resources->createTexture("assets/worlds/add_clouds.png");
}

void World::setWorldAlpha(const Uint8 alpha)
{
	this->worldAlpha = alpha;
}

void World::fadeIn()
{
	this->setWorldAlpha(0);
	this->fadeState = WorldFading::FadeIn;
}

void World::fadeOut()
{
	this->setWorldAlpha(255);
	this->fadeState = WorldFading::FadeOut;
}

void World::setWorldColor(const SDL_Color newColor)
{
	this->worldColor = newColor;
}

void World::setScrollMultiplier(const int mult)
{
	this->scrollSpeedMultiplier = mult;
}

void World::setAllowClouds(const bool state)
{
	this->allowClouds = state;
}

int World::getScrollMultiplier()
{
	return this->scrollSpeedMultiplier;
}

void World::render()
{
	this->scrollingOffset -= (1 * this->scrollSpeedMultiplier);

	if (this->scrollingOffset < -1920)
	{
		this->scrollingOffset = 0;
	}

	// Allows us to have a scrolling background.
	const SDL_Rect r_World = { this->scrollingOffset, 0, 1920, 1080 };
	const SDL_Rect r_World2 = { this->scrollingOffset + 1920, 0, 1920, 1080 };

	switch (this->fadeState)
	{
	case WorldFading::FadeIn:
		this->setWorldAlpha(this->worldAlpha + 1);

		if (this->worldAlpha == 255)
		{
			this->fadeState = WorldFading::Idle;
		}

		break;

	case WorldFading::FadeOut:
		this->setWorldAlpha(this->worldAlpha - 1);

		if (this->worldAlpha == 0)
		{
			this->fadeState = WorldFading::Idle;
		}
		break;
	}

	SDL_SetTextureBlendMode(this->worldTexture, SDL_BLENDMODE_BLEND);

	// World / Cloud color and alpha
	SDL_SetTextureColorMod(this->worldTexture, this->worldColor.r, this->worldColor.g, this->worldColor.b);
	SDL_SetTextureAlphaMod(this->worldTexture, this->worldAlpha);
	SDL_SetTextureColorMod(this->cloudTexture, this->worldColor.r, this->worldColor.g, this->worldColor.b);
	SDL_SetTextureAlphaMod(this->cloudTexture, this->worldAlpha);

	// World render
	SDL_RenderCopy(Globals::engine->getRenderer(), this->worldTexture, NULL, &r_World);
	SDL_RenderCopy(Globals::engine->getRenderer(), this->worldTexture, NULL, &r_World2);

	// Cloud render if allowed
	if (this->allowClouds)
	{
		SDL_RenderCopy(Globals::engine->getRenderer(), this->cloudTexture, NULL, &r_World);
		SDL_RenderCopy(Globals::engine->getRenderer(), this->cloudTexture, NULL, &r_World2);
	}
}