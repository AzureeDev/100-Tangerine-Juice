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
	textureSurface = nullptr;
}

LTexture::~LTexture()
{
	/* Destroy the text (this fixes a memory leak) */
	if (this->currentText != "")
	{
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->textureWidth = 0;
		this->textureHeight = 0;
	}
}

void LTexture::destroy()
{
	this->textureWidth = 0;
	this->textureHeight = 0;
	Globals::resources->destroyTexture(this->texturePath);
	this->texture = nullptr;
}

void LTexture::destroyText()
{
	if (this->texture != nullptr)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
		this->textureWidth = 0;
		this->textureHeight = 0;
	}
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
		this->currentText = text;

		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}
	else
	{
		SDL_Log("LTexture::createText() - Couldn't create a Surface. Error: %s", TTF_GetError());
	}
}

string LTexture::getPath() const
{
	return this->texturePath;
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

Vector2i LTexture::top()
{
	return Vector2i(this->getX(), this->getY());
}

Vector2i LTexture::bottom()
{
	return Vector2i(this->getX(), this->getY() + this->getHeight());
}

int LTexture::right(const bool useSheetSize)
{
	if (useSheetSize)
	{
		return this->getPosition().x + this->getSheetSize();
	}

	return this->getPosition().x + this->getWidth();
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

int LTexture::getAnimationCount()
{
	return this->nbAnimations;
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

void LTexture::setPosition(Vector2i position)
{
	this->texturePosition = position;
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

void LTexture::setFixedSize(const unsigned int fixedSize, const bool keepHeight)
{
	this->fixedSizeSheet = fixedSize;
	this->keepSheetHeight = keepHeight;
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

void LTexture::setScrollable(const bool state, const int multiplier)
{
	this->scrollable = state;
	this->scrollSpeedMultiplier = multiplier;
}

void LTexture::reverseScroll(const bool state)
{
	this->scrollToRight = state;
}

void LTexture::placeMiddleScreen(const bool useSheetSize)
{
	int screenWidth = Globals::engine->getDisplaySettings().w;
	int screenHeight = Globals::engine->getDisplaySettings().h;

	if (!useSheetSize)
	{
		this->setPosition(
			(screenWidth / 2) - this->getWidth() / 2,
			(screenHeight / 2) - this->getHeight() / 2
		);
	}
	else
	{
		this->setPosition(
			(screenWidth / 2) - this->getSheetSize() / 2,
			(screenHeight / 2) - this->getSheetSize() / 2
		);
	}
}

void LTexture::placeLeftScreen()
{
	int screenWidth = Globals::engine->getDisplaySettings().w;
	int screenHeight = Globals::engine->getDisplaySettings().h;

	this->setY((screenHeight / 2) - this->getHeight() / 2);
}

void LTexture::render(SDL_Rect cameraRect)
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
		const int ticks = SDL_GetTicks();

		if (this->nbAnimations > 0)
		{
			this->textureSpriteId = (ticks / this->animationSpeed) % this->nbAnimations;
		}

		const int heightSize = this->keepSheetHeight ? this->getHeight() : this->fixedSizeSheet;

		srcRect = { this->fixedSizeSheet * this->textureSpriteId, 0, this->fixedSizeSheet, this->fixedSizeSheet };
		destRect = { this->getX(), this->getY(), this->fixedSizeSheet, heightSize };

		if (cameraRect.x > 0 || cameraRect.y > 0)
		{
			destRect.x = this->getPosition().x - cameraRect.x;
			destRect.y = this->getPosition().y - cameraRect.y;
		}
	}
	else
	{
		srcRect = { 0, 0, this->getWidth(), this->getHeight() };
		destRect = { this->getX(), this->getY(), this->getWidth(), this->getHeight() };

		if (cameraRect.x > 0 || cameraRect.y > 0)
		{
			destRect.x = this->getPosition().x - cameraRect.x;
			destRect.y = this->getPosition().y - cameraRect.y;
		}
	}

	SDL_Point pt = { 0, 0 };
	const int flipped = this->textureFlipped ? 1 : 0;

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
			Utils::clamp<Uint8>(this->textureColor.a += 5, 0, 255);
			SDL_SetTextureAlphaMod(this->texture, this->getAlpha());

			if (this->textureColor.a >= this->textureBaseColor.a)
			{
				this->setFade(TextureFadingState::Idle);
			}
			break;

		case TextureFadingState::FadeOut:
			Utils::clamp<Uint8>(this->textureColor.a -= 5, 0, 255);
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

	if (this->scrollable)
	{
		/*
			From World.cpp, adapted to a texture
		*/

		if (this->scrollToRight)
		{
			this->scrollingOffset += (1 * this->scrollSpeedMultiplier);

			if (this->scrollingOffset > Globals::engine->getDisplaySettings().wsWidth)
			{
				this->scrollingOffset = 0;
			}

			const SDL_Rect r_scrollableTexture = { this->scrollingOffset, this->getY(), this->getWidth(), this->getHeight() };
			const SDL_Rect r_scrollableTexture2 = { this->scrollingOffset - Globals::engine->getDisplaySettings().wsWidth, this->getY(), this->getWidth(), this->getHeight() };

			SDL_RenderCopy(Globals::engine->getRenderer(), this->texture, NULL, &r_scrollableTexture);
			SDL_RenderCopy(Globals::engine->getRenderer(), this->texture, NULL, &r_scrollableTexture2);
		}
		else
		{
			this->scrollingOffset -= (1 * this->scrollSpeedMultiplier);

			if (this->scrollingOffset < -Globals::engine->getDisplaySettings().wsWidth)
			{
				this->scrollingOffset = 0;
			}

			const SDL_Rect r_scrollableTexture = { this->scrollingOffset, this->getY(), this->getWidth(), this->getHeight() };
			const SDL_Rect r_scrollableTexture2 = { this->scrollingOffset + Globals::engine->getDisplaySettings().wsWidth, this->getY(), this->getWidth(), this->getHeight() };

			SDL_RenderCopy(Globals::engine->getRenderer(), this->texture, NULL, &r_scrollableTexture);
			SDL_RenderCopy(Globals::engine->getRenderer(), this->texture, NULL, &r_scrollableTexture2);
		}

		return;
	}

	SDL_RenderCopyEx(Globals::engine->getRenderer(), this->texture, &srcRect, &destRect, this->textureAngle, &pt, static_cast<SDL_RendererFlip>(flipped));
}