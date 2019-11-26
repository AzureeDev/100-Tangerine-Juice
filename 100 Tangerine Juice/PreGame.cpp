#include "PreGame.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"

const string DEFAULT_WORLD_ID = "ri_se_sky";
const SDL_Color DEFAULT_WORLD_COLOR = { 79, 202, 255, 255 };

PreGame::PreGame()
{
	LilacClasses::PreGame = this;
}

PreGame::~PreGame()
{
	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		Globals::UI->destroyButton(this->unitPickButtons[i].unitIdentifier + "_pickBtn");
	}

	Globals::UI->destroyButton("startTangerine");
}

void PreGame::init()
{
	/* Reverse back to normal, since the main menu had to reverse once for the buttons. */
	std::reverse(UnitDefinitions::def.begin(), UnitDefinitions::def.end());

	OverlayManager::fadeOut(3);
	MusicManager::playMusic("assets/musics/begins.mp3");

	pregameBg.setNewTexture("assets/ui/ig/characterSelectBg.png");
	selectedWorld = World("assets/worlds/" + DEFAULT_WORLD_ID + ".png");
	selectedWorld.setWorldColor(DEFAULT_WORLD_COLOR);
	selectedWorld.setAllowClouds(true);
	selectedWorld.setScrollMultiplier(3);

	/* Create our pick buttons and give a callback */
	for (const auto& unitData : UnitDefinitions::def)
	{
		LButton* btn = Globals::UI->createButton(unitData.unitId + "_pickBtn", "assets/units/" + unitData.unitId + "/_select.png");
		btn->getTexture().setColor({ 125, 125, 125, 255 }, true);
		btn->setHighlightColor({ 255, 255, 255, 255 });
		btn->supplyCallback([this, unitData]() {
			this->setPickedUnit(unitData.unitId);
		});

		this->unitPickButtons.push_back({ unitData.unitId, btn });
	}

	/* Then position them */
	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		/* Base pos, base the others on it afterwards */
		if (i == 0)
		{
			this->unitPickButtons[i].unitButton->setPosition(
				{
					810,
					200
				}
			);
		}
		else
		{
			this->unitPickButtons[i].unitButton->setPosition(
				{
					this->unitPickButtons[i - 1].unitButton->getX() + this->unitPickButtons[i - 1].unitButton->getTexture().getWidth() - 10,
					200
				}
			);
		}
		
	}

	unitPickLabel.createText("UNITS", { 25, 25, 25, 255 });
	unitPickLabel.setPosition(
		{
			this->unitPickButtons[0].unitButton->getTexture().top().x + 32,
			this->unitPickButtons[0].unitButton->getTexture().top().y - unitPickLabel.getHeight() - 5,
		}
	);

	startGame = Globals::UI->createButton("startTangerine", "assets/ui/ig/gameStartBtn.png");
	startGame->setEnabled(false);
	startGame->getTexture().setColor({ 255, 255, 255, 100 }, true);
	startGame->setHighlightColor({ 171, 199, 209 });
	startGame->supplyCallback([this]()
		{
			this->onGameStart();
			MusicManager::fadeOutMusic();
			OverlayManager::fadeIn(3);

			Globals::timer->createTimer("tangerineStartDelay", 2.5f, [this]() {
				Globals::engine->createClass("Tangerine", new Tangerine(this->getGameParams()));
				Globals::engine->destroyClass("PreGame");
			}, 1);
		}
	);
	startGame->setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - (1260 / 2) - (startGame->getTexture().getWidth() / 2),
			Globals::engine->getDisplaySettings().wsHeight - startGame->getTexture().getHeight() - 10
		}
	);

	this->createTopBar();
}

void PreGame::createTopBar()
{
	topBar.setNewTexture("assets/ui/rect_base.png");
	topBar.setSize(Globals::engine->getDisplaySettings().wsWidth, 96);
	topBar.setY(32);
	topBar.setColor({ 12, 12, 12, 255 }, true);

	topBarScroll.setNewTexture("assets/ui/main_menu/topBar.png");
	topBarScroll.setScrollable(true);
	topBarScroll.reverseScroll(true);
	topBarScroll.setPosition(
		{
			0,
			topBar.getY() + 3
		}
	);

	topBarScroll.setColor({ 84, 198, 255, 255 }, true);

	topBarScrollLabel.createText("PREPARATION", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontLarge"));
	topBarScrollLabel.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - topBarScrollLabel.getWidth() - 20,
			topBarScroll.getY() + (topBarScroll.getHeight() / 2) - (topBarScrollLabel.getHeight() / 2) + 5
		}
	);
}

void PreGame::setPickedUnit(const string unitId)
{
	this->gameParameters.pickedUnit = unitId;
	this->onPickedUnit(unitId);
}

void PreGame::onPickedUnit(const string unitPicked)
{
	unitPickedArt.setNewTexture("assets/units/" + unitPicked + "/_art.png");
	unitPickedArt.setTextureFlip(true);
	unitPickedArt.setColor({ 255, 255, 255, 255 }, true);
	unitPickedArt.setPosition(
		{
			-140,
			Globals::engine->getDisplaySettings().wsHeight - unitPickedArt.getHeight() + 128
		}
	);
	unitPickedArt.setFade(TextureFadingState::FadeIn);

}

void PreGame::onGameStart()
{
	this->gameLaunched = true;

	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		this->unitPickButtons[i].unitButton->setEnabled(false);
	}

	startGame->getTexture().setColor({ 255, 255, 255, 100 }, true);
	startGame->setEnabled(false);
}

GameParams PreGame::getGameParams() const
{
	return this->gameParameters;
}

void PreGame::update(const float dt)
{
	/* Handle the button being disabled on the active unit, as well the color of the button */
	if (this->gameParameters.pickedUnit != "" && !this->gameLaunched)
	{
		for (const auto& unitPickBtn : this->unitPickButtons)
		{
			if (unitPickBtn.unitIdentifier == this->gameParameters.pickedUnit)
			{
				unitPickBtn.unitButton->getTexture().setColor({ 255, 255, 255, 255 }, true);
				unitPickBtn.unitButton->setEnabled(false);
			}
			else
			{
				unitPickBtn.unitButton->getTexture().setColor({ 125, 125, 125, 255 }, true);
				unitPickBtn.unitButton->setEnabled(true);
			}
		}

		startGame->setEnabled(true);
		startGame->getTexture().setColor({ 255, 255, 255, 255 }, true);
	}

	/* World, bg & unit art */
	selectedWorld.render();
	unitPickedArt.render();
	pregameBg.render();

	/* Unit btns */
	for (const auto& unitPickBtn : this->unitPickButtons)
	{
		unitPickBtn.unitButton->render();
	}

	/* Labels */
	unitPickLabel.render();

	/* Top bar */
	topBar.render();
	topBarScroll.render();
	topBarScrollLabel.render();

	/* Start btn */
	startGame->render();
}