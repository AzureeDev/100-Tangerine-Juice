#include "Unit.h"
#include "Globals.h"

const unsigned int UNIT_SHEET_SIZE = 512;

Unit::Unit()
{
	/*
		Empty constructor for class members
	*/
}

Unit::Unit(const string unitIdentifier, const string defaultAnimation)
{
	this->unitId = unitIdentifier;
	this->unitAnimation = defaultAnimation;
	this->currentAnimation = defaultAnimation;
	this->unitTexture.setFixedSize(UNIT_SHEET_SIZE);
	this->unitTexture.setNewTexture("assets/units/" + this->unitId + "/" + this->unitAnimation + ".png");
}

string Unit::identifier()
{
	return this->unitId;
}

LTexture& Unit::texture()
{
	return this->unitTexture;
}

Vector2i Unit::position()
{
	return this->unitPosition;
}

int Unit::x()
{
	return this->unitPosition.x;
}

int Unit::y()
{
	return this->unitPosition.y;
}

void Unit::setAnimation(const string newAnimation)
{
	if (newAnimation == this->currentAnimation)
	{
		return;
	}

	this->currentAnimation = newAnimation;

	for (const auto& cosmetics : this->currentCosmetics.identifiers)
	{
		if (cosmetics.second != "")
		{
			this->applyCosmetic(cosmetics.second, cosmetics.first);
		}
	}

	SDL_Log("Animation changed to %s", newAnimation.c_str());
	this->unitTexture.setNewTexture("assets/units/" + this->unitId + "/" + newAnimation + ".png");
}

void Unit::setDash(const bool state, const int multiplier)
{
	this->unitDashing = state;
	this->unitDashMultiplier = multiplier;
}

void Unit::setX(const int x)
{
	this->unitTexture.setX(x);
	this->unitPosition.x = x;

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->setX(x);
	}
}

void Unit::setY(const int y)
{
	this->unitTexture.setY(y);
	this->unitPosition.y = y;

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->setY(y);
	}
}

void Unit::setPosition(const Vector2i pos)
{
	this->unitPosition = pos;
	this->unitTexture.setPosition(pos);

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->setPosition(pos);
	}
}

void Unit::setFlipped(const bool state)
{
	this->unitTexture.setTextureFlip(state);
	this->unitFlipped = state;

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->setTextureFlip(state);
	}
}

void Unit::setStatusMessage(const string message, const SDL_Color color)
{
	this->statusMessage.createText(message, color, 0, Globals::resources->getFont("bleachFontMedium"));
	this->statusMessage.setFade(TextureFadingState::FadeOut);
	this->statusMessage.setPosition(
		{
			this->unitTexture.getPosition().x + (this->unitTexture.getSheetSize() / 2) + 64,
			this->unitTexture.getPosition().y + (this->unitTexture.getHeight() / 2) - 96
		}
	);
}

void Unit::setFade(const TextureFadingState state, const int mult)
{
	this->unitTexture.setFade(state, mult);

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->setFade(state, mult);
	}
}

void Unit::placeMiddleScreen()
{
	this->unitTexture.placeMiddleScreen(true);

	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->placeMiddleScreen(true);
	}

	this->unitPosition = this->unitTexture.getPosition();
}

void Unit::applyCosmetic(const string cosmeticIdentifier, const string type)
{
	this->currentCosmetics.identifiers[type] = cosmeticIdentifier;
	const string cosmeticPath = "assets/units/" + this->identifier() + "/cosmetics/" + type + "/" + cosmeticIdentifier + "/" + this->currentAnimation + ".png";

	if (this->currentCosmetics.textures.count(type) == 0)
	{
		this->currentCosmetics.textures.insert({ type, shared_ptr<LTexture>(new LTexture) });
	}
		
	this->currentCosmetics.textures.find(type)->second->setFixedSize(UNIT_SHEET_SIZE);
	this->currentCosmetics.textures.find(type)->second->setNewTexture(cosmeticPath);
	this->currentCosmetics.textures.find(type)->second->setPosition(this->position());
	this->currentCosmetics.textures.find(type)->second->setTextureFlip(this->unitFlipped);
}

void Unit::render(SDL_Rect camera)
{
	this->unitTexture.render();
	
	for (const auto& cosmetic : this->currentCosmetics.textures)
	{
		cosmetic.second->render();
	}

	this->statusMessage.render();

	if (this->statusMessage.getAlpha() > 0)
	{
		this->statusMessage.setPosition(
			{
				this->unitTexture.getPosition().x + (this->unitTexture.getSheetSize() / 2) + 64,
				this->statusMessage.getY() - 2
			}
		);
	}

	if (this->unitDashing)
	{
		if (this->unitFlipped)
		{
			this->setX(this->x() + (1 * this->unitDashMultiplier));
		}
		else
		{
			this->setX(this->x() - (1 * this->unitDashMultiplier));
		}
	}
}