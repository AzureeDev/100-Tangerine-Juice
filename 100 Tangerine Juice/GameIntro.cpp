#include "GameIntro.h"
#include <SDL.h>
#include "Globals.h"

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
	this->introUnit = Unit("sora", "swordplay");
	this->introUnit.texture().setAnimationSpeed(96);
	this->introUnit.placeMiddleScreen();
	this->introUnit.texture().setFade(TextureFadingState::FadeIn);

	if (!Globals::account->accountCreated())
	{
		this->introPlayerNameInput = Globals::UI->createTextInput("playerNameInput");
		this->introPlayerNameInput->setPosition(
			{
				(Globals::engine->getDisplaySettings().wsWidth / 2) - (this->introPlayerNameInput->getTexture().getWidth() / 2),
				this->introUnit.texture().bottom().y
			}
		);

		this->gameIntroLabel.createText("Hello! Enter your name below!", { 225, 225, 225 }, NULL, Globals::resources->getFont("defaultFontLarge"));
		this->gameIntroLabel.setPosition(this->introUnit.texture().top());
		this->gameIntroLabel.placeMiddleX();
		this->gameIntroLabel.setFade(TextureFadingState::FadeIn);

		this->introBtn = Globals::UI->createButton("introBtn", "assets/ui/rect_base.png");
		this->introBtn->getTexture().setSize(192, 34);
		this->introBtn->setHighlightColor({ 175, 245, 255, 255 });
		this->introBtn->setTextColor({ 25, 25, 25, 255 });
		this->introBtn->setPosition(
			{
				(Globals::engine->getDisplaySettings().wsWidth / 2) - (this->introBtn->getTexture().getWidth() / 2),
				this->introPlayerNameInput->getTexture().bottom().y + 32
			}
		);
		this->introBtn->setText("Start");
		this->introBtn->supplyCallback([this]() 
			{
				Globals::engine->getPlayerData()->set("account.playerName", this->getPlayerNameInput()->getCurrentString());
				Globals::engine->createClass("MainMenu", new MainMenu);
				Globals::engine->destroyClass("GameIntro");
			}
		);
		return;
	}

	this->gameIntroLabel.createText("Click anywhere to begin!", { 225, 225, 225 }, NULL, Globals::resources->getFont("defaultFontLarge"));
	this->gameIntroLabel.setPosition(this->introUnit.texture().bottom());
	this->gameIntroLabel.setFade(TextureFadingState::FadeIn);

	this->introBtn = Globals::UI->createButton("introBtn");
	this->introBtn->getTexture().setSize(Globals::engine->getDisplaySettings().w, Globals::engine->getDisplaySettings().h);
	this->introBtn->supplyCallback(ButtonCallbacks::proceedToMainMenu);
}

shared_ptr<LTextInput>& GameIntro::getPlayerNameInput()
{
	return this->introPlayerNameInput;
}

void GameIntro::update(const float dt)
{
	if (this->introPlayerNameInput != nullptr)
	{
		this->introPlayerNameInput->render();

		if (this->introPlayerNameInput->getCurrentString().empty())
		{
			this->introBtn->disable();
		}
		else
		{
			this->introBtn->activate();
		}
	}

	this->introUnit.render(Globals::engine->getCamera());
	this->gameIntroLabel.render();
	this->introBtn->render();
}