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
	this->unitTexture.setFixedSize(UNIT_SHEET_SIZE);
	this->unitTexture.setNewTexture("assets/units/" + this->unitId + "/" + this->unitAnimation + ".png");
}

LTexture& Unit::texture()
{
	return this->unitTexture;
}

void Unit::setPosition(const Vector2i pos)
{
	this->unitPosition = pos;
	this->unitTexture.setPosition(pos);
}

void Unit::placeMiddleScreen()
{
	this->unitTexture.placeMiddleScreen(true);
	this->unitPosition = this->unitTexture.getPosition();
}

void Unit::render()
{
	this->unitTexture.render();
}