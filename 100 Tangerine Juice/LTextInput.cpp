#include "LTextInput.h"
#include "Globals.h"

LTextInput::LTextInput()
{
	this->moduleActive = true;
}

LTextInput::~LTextInput()
{
	this->moduleTextTexture.destroyText();
}

void LTextInput::init()
{
	this->moduleBackground.setNewTexture("assets/ui/rect_base.png");
	this->moduleBackground.setColor({ 25, 25, 25, 255 }, true);
	this->moduleBackground.setSize(128 * 3, 38);

	this->onModuleClick();
	this->buildString();
}

void LTextInput::onModuleClick()
{
	if (!Globals::timer->hasTimer("textInputBarFade"))
	{
		Globals::timer->createTimer("textInputBarFade", 0.5f, [this]()
			{
				if (this->getVerticalBar().getAlpha() == 255)
				{
					this->getVerticalBar().setAlpha(0);
				}
				else if (this->getVerticalBar().getAlpha() == 0)
				{
					this->getVerticalBar().setAlpha(255);
				}
			}
		);
	}
}

void LTextInput::onBackspacePress()
{
	if (this->moduleActive && !this->moduleTextContainer.empty())
	{
		this->moduleTextContainer.pop_back();
		this->buildString();
	}
}

void LTextInput::onKeyPress(string& character)
{
	if (this->moduleActive && this->moduleTextContainer.size() < this->moduleCharacterLimit)
	{
		// Check if the character is allowed
		if (std::find(this->moduleAllowedCharacters.begin(), this->moduleAllowedCharacters.end(), character) != this->moduleAllowedCharacters.end())
		{
			this->moduleTextContainer.push_back(character);
			this->buildString();
		}
	}
}

void LTextInput::buildString()
{
	this->moduleText = "";

	for (const auto& character : this->moduleTextContainer)
	{
		this->moduleText += character;
	}

	this->moduleTextVerticalBar.createText("|", { 225, 225, 225, 255 }, 0, Globals::resources->getFont("defaultFont"));
	this->moduleTextTexture.createText(this->moduleText, { 255, 255, 255, 255}, 0, Globals::resources->getFont("defaultFont"));

	this->moduleTextVerticalBar.setPosition(
		{
			this->moduleTextTexture.right(),
			this->moduleTextTexture.getY()
		}
	);
}

bool LTextInput::isMouseInside() const
{
	return false;
}

LTexture& LTextInput::getVerticalBar()
{
	return this->moduleTextVerticalBar;
}

void LTextInput::setPosition(Vector2i position)
{
	this->modulePosition = position;
	this->moduleBackground.setPosition(position);
}

LTexture& LTextInput::getTexture()
{
	// Other elements are based on this
	return this->moduleBackground;
}

string& LTextInput::getCurrentString()
{
	return this->moduleText;
}

bool LTextInput::isActive()
{
	return this->moduleActive;
}

void LTextInput::render()
{
	this->moduleTextTexture.setPosition(this->moduleBackground.getPosition().x + 10, this->moduleBackground.getPosition().y + 10);
	this->moduleTextVerticalBar.setPosition(this->moduleTextTexture.right(), this->moduleTextTexture.getY());

	this->moduleBackground.render();
	this->moduleTextTexture.render();
	this->moduleTextVerticalBar.render();
}
