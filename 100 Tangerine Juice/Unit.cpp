#include "Unit.h"

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
	this->unitShadow.setNewTexture("assets/units/shared/shadow.png");
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
}

void Unit::setY(const int y)
{
	this->unitTexture.setY(y);
	this->unitPosition.y = y;
}

void Unit::setPosition(const Vector2i pos)
{
	this->unitPosition = pos;
	this->unitTexture.setPosition(pos);
	this->unitShadow.setPosition(
		{
			pos.x + (this->unitTexture.getSheetSize() / 2) - (this->unitShadow.getWidth() / 2),
			pos.y + this->unitTexture.getHeight() - this->unitShadow.getHeight() - 96
		}
	);
}

void Unit::setFlipped(const bool state)
{
	this->unitTexture.setTextureFlip(state);
	this->unitFlipped = state;
}

void Unit::placeMiddleScreen()
{
	this->unitTexture.placeMiddleScreen(true);
	this->unitShadow.setPosition(
		{
			this->unitTexture.getX() + (this->unitTexture.getSheetSize() / 2) - (this->unitShadow.getWidth() / 2),
			this->unitTexture.getY() + this->unitTexture.getHeight() - this->unitShadow.getHeight() - 96
		}
	);

	this->unitPosition = this->unitTexture.getPosition();
}

void Unit::render(SDL_Rect cameraRect)
{
	//this->unitShadow.render();
	this->unitTexture.render();

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