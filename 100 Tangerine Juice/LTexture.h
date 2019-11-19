#pragma once
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

#include "Vector2.h"

using std::string;

enum class TextureFadingState {
	Idle,
	FadeIn,
	FadeOut
};

class LTexture
{
private:
	SDL_Texture* texture = nullptr;
	string texturePath = "";
	SDL_Color textureBaseColor = { 255, 255, 255, 255 };
	SDL_Color textureColor = { 255, 255, 255, 255 };
	SDL_Color textureHighlightColor = { 255, 255, 255, 255 }; // Used by LButton
	TextureFadingState textureFadeState = TextureFadingState::Idle;
	int textureWidth = 0;
	int textureHeight = 0;
	int fixedSizeSheet = 0;
	int animationSpeed = 100;
	int nbAnimations = 0;
	int textureAngle = 0;
	bool textureFlipped = false;
	bool scrollable = false;
	int scrollingOffset = 0;
	int scrollSpeedMultiplier = 1;
	bool scrollToRight = false;
	Vector2i texturePosition = { 0, 0 };
	Uint8 textureSpriteId = 0;

public:
	LTexture();
	LTexture(const string path);
	void destroy();
	void hide();
	void createText(const string text, const SDL_Color color = { 150, 150, 150, 255 }, const int maxLength = 0, TTF_Font* custom_font = nullptr);
	int getWidth();
	int getHeight();
	int getSheetSize();
	int getX();
	int getY();
	Vector2i top();
	Vector2i bottom();
	Vector2i getPosition();
	SDL_Color getColor();
	int getAlpha();
	SDL_Color getHighlightColor();
	void resetBaseColor();
	void setColor(const SDL_Color color, const bool setDefault = false);
	void setColorNoAlpha(const SDL_Color color);
	void setHighlightColor(const SDL_Color color);
	void setBaseColor(const SDL_Color color);
	void setAlpha(int alpha);
	void setX(const int x);
	void setY(const int y);
	void setPosition(Vector2i position);
	void setPosition(const int x, const int y);
	void setHeight(const int newHeight);
	void setWidth(const int newWidth);
	void setSize(const int w, const int h);
	void setFixedSize(const unsigned int fixedSize);
	void setTextureFlip(const bool state);
	void setAngle(const int newAngle);
	void setAnimationCount(const unsigned int animCount);
	void setAnimationSpeed(const unsigned int animSpeed);
	void setNewTexture(const string path);
	void setFade(const TextureFadingState state);
	void setScrollable(const bool state, const int multiplier = 1);
	void reverseScroll(const bool state);
	void placeMiddleScreen(const bool useSheetSize = false);
	void render();
};
