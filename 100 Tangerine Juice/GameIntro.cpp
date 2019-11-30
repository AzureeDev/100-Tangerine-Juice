#include "GameIntro.h"
#include <SDL.h>
#include "Globals.h"

#ifdef TANGERINE_DEBUG
#include "Tangerine.h"
#endif

GameIntro::GameIntro()
{
	/*
		Initializer to our globals so we can mess with this instance everywhere.
	*/

	LilacClasses::GameIntro = this;
}

GameIntro::~GameIntro()
{
	Globals::UI->destroyButton("introBtn");
}

void GameIntro::init()
{
#ifdef TANGERINE_DEBUG
	Globals::engine->createClass("Tangerine", new Tangerine({ "suguri", "ri_se_sky", GameParams::WorldGeneration::Battlefield }));
	Globals::engine->destroyClass("GameIntro");
#else
	this->introUnit = Unit("sora", "swordplay");
	this->introUnit.texture().setAnimationSpeed(96);
	this->introUnit.placeMiddleScreen();
	this->introUnit.texture().setFade(TextureFadingState::FadeIn);

	this->gameIntroLabel.createText("Press left click to begin", { 225, 225, 225 }, NULL, Globals::resources->getFont("defaultFontLarge"));
	this->gameIntroLabel.setPosition(this->introUnit.texture().bottom());
	this->gameIntroLabel.setFade(TextureFadingState::FadeIn);

	this->introBtn = Globals::UI->createButton("introBtn");
	this->introBtn->getTexture().setSize(Globals::engine->getDisplaySettings().w, Globals::engine->getDisplaySettings().h);
	this->introBtn->supplyCallback(ButtonCallbacks::proceedToMainMenu);
#endif
}

void GameIntro::update(const float dt)
{
#ifndef TANGERINE_DEBUG
	this->introUnit.render(Globals::engine->getCamera());
	this->gameIntroLabel.render();
	this->introBtn->render();
#endif
}