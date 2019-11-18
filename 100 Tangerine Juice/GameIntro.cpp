#include "GameIntro.h"
#include <SDL.h>
#include "Globals.h"

GameIntro::GameIntro() : LClass(this)
{
}

void GameIntro::init()
{
	this->introUnit = Unit("sora_m", "intro");
	this->introUnit.placeMiddleScreen();
	this->introUnit.texture().setFade(TextureFadingState::FadeIn);

	this->gameIntroLabel.createText("Press left click to begin", { 225, 225, 225 }, NULL, Globals::resources->getFont("defaultFontLarge"));
	this->gameIntroLabel.setPosition(this->introUnit.texture().bottom());
	this->gameIntroLabel.setFade(TextureFadingState::FadeIn);

	this->introBtn = Globals::UI->createButton("introBtn");
	this->introBtn->getTexture().setSize(Globals::engine->getDisplaySettings().w, Globals::engine->getDisplaySettings().h);
}

void GameIntro::update(const float dt)
{
	this->introUnit.render();
	this->gameIntroLabel.render();
	this->introBtn->render();
}