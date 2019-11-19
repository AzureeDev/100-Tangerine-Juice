#include "MainMenu.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"

MainMenu::MainMenu() : LClass(this)
{
	LilacClasses::MainMenu = this;
}

void MainMenu::init()
{
	MusicManager::playMusic("assets/musics/mainmenu.mp3");
	OverlayManager::fadeOut(3);

	this->createWorld();
	this->createLeftPanel();
	this->createTopBar();
}

void MainMenu::createWorld()
{
	const vector<string> worlds = {
		"assets/worlds/ml_sky_bw.png",
		"assets/worlds/wire_bw.png",
		"assets/worlds/ri_se_sky.png"
	};

	const int worldChosen = rand() % worlds.size();

	world.setNewWorld(worlds[worldChosen]);

	if (worldChosen == 2) // ri_se_sky for clouds
	{
		world.setAllowClouds(true);
	}

	world.setWorldColor({ 79, 202, 255, 255 });
	world.setScrollMultiplier(9);
}

void MainMenu::createLeftPanel()
{
	leftPanel.setNewTexture("assets/ui/main_menu/main_menu_bg.png");
	leftPanel.setColor({ 235, 235, 235, 255 }, true);

	/* Game Logo */

	gameLogo.setNewTexture("assets/ui/game_logo.png");
	gameLogo.setPosition(
		{
			(500 / 2) - gameLogo.getWidth() / 2,
			32
		}
	);

	gameStart = Globals::UI->createButton("gameStart", "assets/ui/main_menu/menu_btn.png");
	characterDatabase = Globals::UI->createButton("characterDatabase", "assets/ui/main_menu/menu_btn.png");
	gameCredits = Globals::UI->createButton("gameCredits", "assets/ui/main_menu/menu_btn.png");
	gameQuit = Globals::UI->createButton("gameQuit", "assets/ui/main_menu/menu_btn.png");

	gameQuit->supplyCallback(ButtonCallbacks::quitGame);

	const vector<LButton*> lbuttons = {
		gameStart,
		characterDatabase,
		gameCredits,
		gameQuit
	};

	/*
		Auto position depending on the vector above
	*/
	for (size_t i = 0; i < lbuttons.size(); ++i)
	{
		if (i == 0)
		{
			lbuttons[i]->setPosition({ (500 / 2) - gameStart->getTexture().getWidth() / 2, gameLogo.bottom().y + 64 });
		}
		else
		{
			lbuttons[i]->setPosition({ lbuttons[i - 1]->getX(), lbuttons[i - 1]->getY() + lbuttons[i - 1]->getTexture().getHeight() + 10 });
		}
		
		lbuttons[i]->setTextColor({ 20, 20, 20, 255 });
		lbuttons[i]->getTexture().setColor({ 255, 255, 255, 255 }, true);
		lbuttons[i]->setHighlightColor({ 171, 199, 209 });
	}

	gameStart->setText("Start");
	characterDatabase->setText("Unit Database");
	gameCredits->setText("Credits");
	gameQuit->setText("Exit");

	engineVersionLabel.createText("LilacEngine v" + Globals::engine->getVersion() + " | @Sora #7688", { 15, 15, 15, 255 });
	engineVersionLabel.setPosition(
		{
			(500 / 2) - engineVersionLabel.getWidth() / 2,
			Globals::engine->getDisplaySettings().wsHeight - engineVersionLabel.getHeight() - 10
		}
	);
}

void MainMenu::createTopBar()
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

	topBarScrollLabel.createText("MAIN MENU", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontLarge"));
	topBarScrollLabel.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - topBarScrollLabel.getWidth() - 20,
			topBarScroll.getY() + (topBarScroll.getHeight() / 2) - (topBarScrollLabel.getHeight() / 2) + 5
		}
	);
}

void MainMenu::update(const float dt)
{
	// World layer
	world.render();

	// Top Bar layer
	topBar.render();
	topBarScroll.render();
	topBarScrollLabel.render();

	// Left panel layer
	leftPanel.render();

	// Buttons
	gameStart->render();
	characterDatabase->render();
	gameCredits->render();
	gameQuit->render();

	engineVersionLabel.render();
	gameLogo.render();
}