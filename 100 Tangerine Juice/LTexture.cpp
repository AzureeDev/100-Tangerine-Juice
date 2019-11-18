#include <SDL.h>
#include "Globals.h"
#include "LTexture.h"
#include "Utils.h"

/*
	LTexture - SDL Texture wrapper

	Contains a lot of utilities to make the rendering, positioning and manipulation of a texture in a easier way.
*/

LTexture::LTexture()
{
}

LTexture::LTexture(const string path)
{
	this->texturePath = path;
	this->texture = Globals::resources->createTexture(path);

	// Get Dimensions
	SDL_Surface* textureSurface = IMG_Load(path.c_str());
	if (textureSurface != NULL)
	{
		this->textureWidth = textureSurface->w;
		this->textureHeight = textureSurface->h;
	}
	SDL_FreeSurface(textureSurface);
}

void LTexture::destroy()
{
	this->textureWidth = 0;
	this->textureHeight = 0;
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
}

void LTexture::hide()
{
	this->textureWidth = 0;
	this->textureHeight = 0;
}

void LTexture::createText(const string text, const SDL_Color color, const int maxLength, TTF_Font* custom_font)
{
	if (this->texture != nullptr)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->textureWidth = 0;
		this->textureHeight = 0;
	}

	if (custom_font == nullptr)
	{
		custom_font = Globals::resources->getFont("defaultFont");
	}

	const unsigned int textMaxLength = maxLength == 0 ? Globals::engine->getDisplaySettings().w : maxLength;
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(custom_font, text.c_str(), color, textMaxLength);

	if (textSurface != nullptr)
	{
		this->texture = SDL_CreateTextureFromSurface(Globals::engine->getRenderer(), textSurface);
		this->textureWidth = textSurface->w;
		this->textureHeight = textSurface->h;

		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}
	else
	{
		SDL_Log("LTexture::createText() - Couldn't create a Surface. Error: %s", TTF_GetError());
	}
}

int LTexture::getWidth()
{
	return this->textureWidth;
}

int LTexture::getHeight()
{
	return this->textureHeight;
}

int LTexture::getSheetSize()
{
	return this->fixedSizeSheet;
}

int LTexture::getX()
{
	return this->texturePosition.x;
}

int LTexture::getY()
{
	return this->texturePosition.y;
}

Vector2i LTexture::getPosition()
{
	return this->texturePosition;
}

SDL_Color LTexture::getColor()
{
	return this->textureColor;
}

int LTexture::getAlpha()
{
	return this->textureColor.a;
}

SDL_Color LTexture::getHighlightColor()
{
	return this->textureHighlightColor;
}

void LTexture::resetBaseColor()
{
	this->textureColor = {
		this->textureBaseColor.r,
		this->textureBaseColor.g,
		this->textureBaseColor.b,
		static_cast<Uint8>(this->getAlpha())
	};
}

void LTexture::setColor(const SDL_Color color, const bool setDefault)
{
	if (setDefault)
	{
		this->textureBaseColor = color;
	}

	this->textureColor = color;
}

void LTexture::setColorNoAlpha(const SDL_Color color)
{
	this->setColor({
		color.r,
		color.g,
		color.b,
		static_cast<Uint8>(this->getAlpha())
		});
}

void LTexture::setHighlightColor(const SDL_Color color)
{
	this->textureHighlightColor = color;
}

void LTexture::setBaseColor(const SDL_Color color)
{
	this->textureBaseColor = color;
}

void LTexture::setAlpha(int alpha)
{
	alpha = Utils::clamp(alpha, 0, 255);

	SDL_Color currentColor = this->textureColor;
	SDL_Color newColor = { currentColor.r, currentColor.g, currentColor.b, static_cast<Uint8>(alpha) };

	this->textureColor = newColor;
}

void LTexture::setX(const int x)
{
	this->texturePosition.x = x;
}

void LTexture::setY(const int y)
{
	this->texturePosition.y = y;
}

void LTexture::setPosition(const int x, const int y)
{
	this->texturePosition = { x, y };
}

void LTexture::setHeight(const int newHeight)
{
	this->textureHeight = newHeight;
}

void LTexture::setWidth(const int newWidth)
{
	this->textureWidth = newWidth;
}

void LTexture::setSize(const int w, const int h)
{
	this->textureWidth = w;
	this->textureHeight = h;
}

void LTexture::setFixedSize(const unsigned int fixedSize)
{
	this->fixedSizeSheet = fixedSize;
}

void LTexture::setTextureFlip(const bool state)
{
	this->textureFlipped = state;
}

void LTexture::setAngle(const int newAngle)
{
	this->textureAngle = newAngle;
}

void LTexture::setAnimationCount(const unsigned int animCount)
{
	this->nbAnimations = animCount;
}

void LTexture::setAnimationSpeed(const unsigned int animSpeed)
{
	this->animationSpeed = animSpeed;
}

void LTexture::setNewTexture(const string path)
{
	if (path == this->texturePath)
	{
		return;
	}

	this->texture = Globals::resources->createTexture(path);
	this->texturePath = path;

	// Get Dimensions
	SDL_Surface* textureSurface = IMG_Load(path.c_str());
	if (textureSurface != NULL)
	{
		this->textureWidth = textureSurface->w;
		this->textureHeight = textureSurface->h;
	}

	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	if (this->fixedSizeSheet > 0)
	{
		// Guess anim count
		this->setAnimationCount(static_cast<unsigned int>(this->textureWidth / this->fixedSizeSheet));
	}
}

void LTexture::setFade(const TextureFadingState state)
{
	if (state != TextureFadingState::Idle)
	{
		if (state == TextureFadingState::FadeIn)
		{
			this->setAlpha(0);
		}
		else if (state == TextureFadingState::FadeOut)
		{
			this->setAlpha(this->textureBaseColor.a);
		}
		else
		{
			this->setAlpha(this->getAlpha());
		}
	}

	this->textureFadeState = state;
}

void LTexture::placeMiddleScreen()
{
	int screenWidth = Globals::engine->getDisplaySettings().w;
	int screenHeight = Globals::engine->getDisplaySettings().h;

	this->setPosition(
		(screenWidth / 2) - this->getWidth() / 2,
		(screenHeight / 2) - this->getHeight() / 2
	);
}

void LTexture::render()
{
	if (this->texture == nullptr)
	{
		return;
	}

	if (this->getHeight() == 0 && this->getWidth() == 0)
	{
		return;
	}

	SDL_Rect srcRect;
	SDL_Rect destRect;

	if (this->fixedSizeSheet > 0)
	{
		int ticks = SDL_GetTicks();

		if (this->nbAnimations > 0)
		{
			this->textureSpriteId = (ticks / this->animationSpeed) % this->nbAnimations;
		}

		srcRect = { this->fixedSizeSheet * this->textureSpriteId, 0, this->fixedSizeSheet, this->fixedSizeSheet };
		destRect = { this->getX(), this->getY(), this->fixedSizeSheet, this->fixedSizeSheet };
	}
	else
	{
		srcRect = { 0, 0, this->getWidth(), this->getHeight() };
		destRect = { this->getX(), this->getY(), this->getWidth(), this->getHeight() };
	}

	SDL_Point pt = { 0, 0 };
	SDL_RendererFlip flipped = this->textureFlipped ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(
		this->texture,
		Utils::unpackColor(this->textureColor)[static_cast<int>(ColorIndex::Red)],
		Utils::unpackColor(this->textureColor)[static_cast<int>(ColorIndex::Green)],
		Utils::unpackColor(this->textureColor)[static_cast<int>(ColorIndex::Blue)]
	);

	if (this->textureFadeState != TextureFadingState::Idle)
	{
		switch (this->textureFadeState)
		{
		case TextureFadingState::FadeIn:
			Utils::clamp<Uint8>(this->textureColor.a += 15, 0, 255);
			SDL_SetTextureAlphaMod(this->texture, this->getAlpha());

			if (this->textureColor.a >= this->textureBaseColor.a)
			{
				this->setFade(TextureFadingState::Idle);
			}
			break;

		case TextureFadingState::FadeOut:
			Utils::clamp<Uint8>(this->textureColor.a -= 15, 0, 255);
			SDL_SetTextureAlphaMod(this->texture, this->getAlpha());

			if (this->textureColor.a <= 0)
			{
				this->setFade(TextureFadingState::Idle);
			}
			break;
		}
	}
	else
	{
		SDL_SetTextureAlphaMod(this->texture, Utils::unpackColor(this->textureColor)[static_cast<int>(ColorIndex::Alpha)]);
	}

	SDL_RenderCopyEx(Globals::engine->getRenderer(), this->texture, &srcRect, &destRect, this->textureAngle, &pt, flipped);
}