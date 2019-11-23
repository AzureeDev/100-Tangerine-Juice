#include "Panel.h"
#include "Globals.h"

Panel::Panel()
{
	/* Load up the panel texture */
	panelTexture.setNewTexture("assets/panels/panel_empty.png");
}

void Panel::setPosition(const Vector2i pos)
{
	panelPosition = pos;
	panelTexture.setPosition(pos);
	panelIdentifier.setPosition(
		{
			pos.x + (panelTexture.getWidth() / 2) - (panelIdentifier.getWidth() / 2) - 32,
			pos.y + panelTexture.getHeight() + 8
		}
	);
}

void Panel::setIdentifier(const int id)
{
	panelId = id;
	std::string identifierStr = std::to_string(id);
	
	if (id == 0)
	{
		identifierStr = "Start";
	}
	else if (id == 100)
	{
		identifierStr = "Finish";
	}

	panelIdentifier.createText(identifierStr, { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
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
	panelIdentifier.render(camera);
}
