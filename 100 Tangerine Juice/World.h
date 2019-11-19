#pragma once
#include <SDL.h>
#include <string>

using std::string;

enum class WorldFading {
	Idle,
	FadeIn,
	FadeOut
};

class World
{
private:
	SDL_Texture* worldTexture;
	SDL_Texture* cloudTexture;
	SDL_Color worldColor = { 255, 255, 255 };
	Uint8 worldAlpha = 255;
	WorldFading fadeState = WorldFading::Idle;
	int x = 0;
	int y = 0;
	int scrollSpeedMultiplier = 1;
	int scrollingOffset = 0;
	bool allowClouds = false;

public:
	World();
	World(const string worldTexture);
	SDL_Color getWorldColor();
	void setNewWorld(const string path);
	void setWorldAlpha(const Uint8 alpha);
	void fadeIn();
	void fadeOut();
	void setWorldColor(const SDL_Color newColor);
	void setScrollMultiplier(const int mult);
	void setAllowClouds(const bool state);
	int getScrollMultiplier();

	void render();
};
