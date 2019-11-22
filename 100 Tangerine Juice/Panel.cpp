#include "Panel.h"

Panel::Panel()
{
	/* Load up the panel texture */
	panelTexture.setNewTexture("assets/panels/panel_empty.png");
}

void Panel::setPosition(const Vector2i pos)
{
	panelPosition = pos;
	panelTexture.setPosition(pos);
}

Vector2i& Panel::getPosition()
{
	return this->panelPosition;
}

LTexture& Panel::getTexture()
{
	return this->panelTexture;
}

void Panel::trigger()
{
	/*
		Trigger code goes here
	*/
}

void Panel::render(const SDL_Rect camera)
{
	panelTexture.render(camera);
}
