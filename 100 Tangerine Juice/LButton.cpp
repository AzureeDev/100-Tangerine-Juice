#include "LButton.h"
#include "Globals.h"
#include "SFXManager.h"

/*
	LButton

	Manages a button with automatic event handle.
*/

LButton::LButton()
{
}

LButton::~LButton()
{
	this->buttonVisible = false;
}

LButton::LButton(const string id, const string btnTexturePath)
{
	this->buttonId = id;
	this->buttonTexture.setNewTexture(btnTexturePath);
	this->buttonPath = btnTexturePath;
	this->buttonHeight = this->buttonTexture.getHeight();
	this->buttonWidth = this->buttonTexture.getWidth();
}

LTexture& LButton::getTexture()
{
	return this->buttonTexture;
}

string LButton::getId()
{
	return this->buttonId;
}

bool LButton::isMouseInside()
{
	bool inside = true;

	if (Globals::mousePositionX < this->buttonX)
	{
		inside = false;
	}
	else if (Globals::mousePositionX > this->buttonX + this->buttonTexture.getWidth())
	{
		inside = false;
	}
	else if (Globals::mousePositionY < this->buttonY)
	{
		inside = false;
	}
	else if (Globals::mousePositionY > this->buttonY + this->buttonTexture.getHeight())
	{
		inside = false;
	}

	return inside;
}

bool LButton::isEnabled()
{
	return this->buttonEnabled;
}

void LButton::supplyCallback(const std::function<void()> clbk)
{
	this->buttonCallback = clbk;
}

void LButton::supplyUnitCallback(Unit* unit, std::function<void(Unit*)> clbk)
{
	this->buttonBindedUnit = unit;
	this->buttonUnitCallback = clbk;
}

void LButton::event(const SDL_Event& ev)
{
	if (!this->buttonEnabled)
	{
		return;
	}

	if (ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ev.button.button == SDL_BUTTON_LEFT && this->isMouseInside())
		{
			if (this->allowSound)
			{
				SFXManager::playSFX("btn_clicked");
			}

			if (this->buttonCallback != NULL)
			{
				this->buttonCallback();
			}

			if (this->buttonUnitCallback != NULL)
			{
				this->buttonUnitCallback(this->buttonBindedUnit);
			}

			SDL_Log("Button %s clicked.", this->getId().c_str());
		}
	}
}

int LButton::getX()
{
	return this->buttonX;
}

int LButton::getY()
{
	return this->buttonY;
}

void LButton::setX(const int x)
{
	this->buttonX = x;
	this->buttonTexture.setX(x);
	this->buttonText.setX(x);
}

void LButton::setY(const int y)
{
	this->buttonY = y;
	this->buttonTexture.setY(y);
	this->buttonText.setY(y);
}

void LButton::setPosition(const int x, const int y)
{
	this->buttonX = x;
	this->buttonTexture.setX(x);
	this->buttonY = y;
	this->buttonTexture.setY(y);
	this->buttonText.setPosition(x, y);
}

void LButton::setPosition(const Vector2i pos)
{
	this->setPosition(pos.x, pos.y);
}

void LButton::setVisible(const bool state)
{
	this->buttonVisible = state;
}

void LButton::setEnabled(const bool state)
{
	this->buttonEnabled = state;
}

void LButton::setHighlightColor(const SDL_Color color)
{
	this->buttonHighlightColor = color;
	this->buttonTexture.setHighlightColor(color);
}

void LButton::setText(const string text)
{
	this->buttonTextStr = text;
	this->buttonText.createText(text, this->buttonTextColor, this->buttonTexture.getWidth(), Globals::resources->getFont("defaultFont32"));
	this->buttonText.setPosition(
		this->buttonTexture.getX() + (this->buttonTexture.getWidth() / 2) - buttonText.getWidth() / 2,
		this->buttonTexture.getY() + (this->buttonTexture.getHeight() / 2) - buttonText.getHeight() / 2
	);
}

void LButton::setTextColor(const SDL_Color color)
{
	this->buttonTextColor = color;
}

void LButton::setAllowSound(const bool state)
{
	this->allowSound = state;
}

void LButton::render()
{
	if (this == nullptr)
	{
		return;
	}

	if (this->buttonVisible)
	{
		if (this->isMouseInside())
		{
			if (this->buttonEnabled && this->buttonVisible)
			{
				this->buttonTexture.setColorNoAlpha(this->buttonHighlightColor);

				if (!this->playedSoundHighlight && this->allowSound)
				{
					SFXManager::playSFX("btn_over");
					this->playedSoundHighlight = true;
				}
			}
		}
		else
		{
			this->buttonTexture.resetBaseColor();
			this->playedSoundHighlight = false;
		}

		this->buttonTexture.render();

		if (!this->buttonTextStr.empty())
		{
			this->buttonText.render();
		}
	}
}