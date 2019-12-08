#include "MainMenu.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"
#include "UnitDefinitions.h"
#include "Discord.h"
#include "Utils.h"
#include "Shop.h"

const string DEFAULT_BUTTON_TEXTURE = "assets/ui/main_menu/menu_btn.png";

MainMenu::MainMenu()
{
	LilacClasses::MainMenu = this;
}

MainMenu::~MainMenu()
{
	Globals::timer->removeTimer("mmUnit1_clbk");
}

void MainMenu::init()
{
	MusicManager::playMusic("assets/musics/mainmenu.mp3");
	OverlayManager::fadeOut(3);
	Discord::setRichPresence(
		{
			"Main Menu"
		}
	);

	/* Reverse the unit vector for buttons */
	std::reverse(UnitDefinitions::def.begin(), UnitDefinitions::def.end());

	this->createWorld();
	this->createFwdUnits();
	this->createLeftPanel();
	this->createTopBar();
	this->createInformationBar();
}

void MainMenu::createWorld()
{
	const vector<string> worlds = {
		"assets/worlds/ml_sky_bw.png",
		"assets/worlds/wire_bw.png",
		"assets/worlds/ri_se_sky.png",
		"assets/worlds/sr_sky.png"
	};

	const int worldChosen = rand() % worlds.size();

	world.setNewWorld(worlds[worldChosen]);

	if (worldChosen == 2) // ri_se_sky for clouds
	{
		world.setAllowClouds(true);
	}

	world.setWorldColor({ 79, 202, 255, 255 });
	world.setScrollMultiplier(3);
}

void MainMenu::createFwdUnits()
{
	Globals::timer->createTimer("mmUnit1_clbk", 6, TimerCallbacks::mainMenuUnitAnimation);
}

void MainMenu::createLeftPanel()
{
	leftPanel.setNewTexture("assets/ui/main_menu/main_menu_bg.png");
	leftPanel.setColor({ 235, 235, 235, 255 }, true);

	/* Game Logo */

	/*
		500 is used here as the left panel "white" width is 500, actual texture include shadows which makes it wider.
	*/

	gameLogo.setNewTexture("assets/ui/game_logo.png");
	gameLogo.setPosition(
		{
			(500 / 2) - gameLogo.getWidth() / 2,
			32
		}
	);

	this->createAccount();
	this->createMainMenuButtons();

	engineVersionLabel.createText("LilacEngine v" + Globals::engine->getVersion() + " | @Sora #7688", { 15, 15, 15, 255 });
	engineVersionLabel.setPosition(
		{
			(500 / 2) - engineVersionLabel.getWidth() / 2,
			Globals::engine->getDisplaySettings().wsHeight - engineVersionLabel.getHeight() - 10
		}
	);
}

void MainMenu::createAccount()
{
	/* Account unit */
	accountUnit = Unit(Globals::account->unit());
	accountUnit.setFlipped(true);
	accountUnit.texture().setPosition({ (500 / 2) - (accountUnit.texture().getSheetSize() / 2) - 128, gameLogo.bottom().y - 64 });

	/* Account name */
	accountName.createText(Globals::account->name(), { 10, 10, 10, 255 }, 280, Globals::resources->getFont("defaultFont36"));
	accountName.setPosition(
		{
			accountUnit.x() + accountUnit.texture().getSheetSize() - 300,
			accountUnit.y() + 308
		}
	);

	accountLevel.createText("LEVEL " + std::to_string(Globals::account->level()), { 45, 45, 45, 255 }, 0, Globals::resources->getFont("defaultFontMedium"));
	accountLevel.setPosition(accountName.bottom());

	accountStarIcon.setNewTexture("assets/ui/star.png");
	accountStarIcon.setPosition(accountLevel.bottom().x, accountLevel.bottom().y + 32);
	accountStarIcon.setColor({ 15, 15, 15, 255 });

	accountStarAmount.createText(Utils::thousandFormat(Globals::account->stars()), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	accountStarAmount.setPosition({ accountStarIcon.right() + 16, accountStarIcon.getY() + (accountStarIcon.getHeight() / 2) - (accountStarAmount.getHeight() / 2) + 3 });
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

void MainMenu::createInformationBar()
{
	informationBar.setNewTexture("assets/ui/rect_base.png");
	informationBar.setColor({ 10, 20, 25, 200 }, true);
	informationBar.setSize(Globals::engine->getDisplaySettings().wsWidth, 48);
	informationBar.setPosition({ 0, topBar.getY() + topBar.getHeight() + 5 });

	informationBarLabel.createText(Globals::engine->getMainMenuMessage(), { 235, 235, 235, 255 });
	informationBarLabel.setScrollable(true, 2);
	informationBarLabel.setPosition({ 0, informationBar.getY() + informationBarLabel.getHeight() / 2 });
}

void MainMenu::createHelpPicture(const string helpPictureTexture)
{
	helpPicture.destroy();
	helpPicture.setPosition(
		{
			500,
			informationBar.bottom().y
		}
	);

	helpPicture.setNewTexture(helpPictureTexture);
	helpPicture.setFade(TextureFadingState::FadeIn, 3);
}

void MainMenu::hideHelpPicture()
{
	helpPicture.destroy();
}

void MainMenu::createBackBtn()
{
	LButton* back = Globals::UI->createButton("back", DEFAULT_BUTTON_TEXTURE);
	back->supplyCallback(ButtonCallbacks::backToMainMenu);
	mainMenuButtons.push_back({ "back", back });
	this->calculateButtonPosition();
	back->setText("Back");
}

void MainMenu::setHeaderTitle(const string newTitle)
{
	topBarScrollLabel.createText(newTitle, { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontLarge"));
	topBarScrollLabel.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - topBarScrollLabel.getWidth() - 20,
			topBarScroll.getY() + (topBarScroll.getHeight() / 2) - (topBarScrollLabel.getHeight() / 2) + 5
		}
	);
	topBarScrollLabel.setFade(TextureFadingState::FadeIn);
}

void MainMenu::clearButtons()
{
	for (size_t i = 0; i < mainMenuButtons.size(); ++i)
	{
		Globals::UI->destroyButton(mainMenuButtons[i].name);
	}

	mainMenuButtons.clear();
}

void MainMenu::calculateButtonPosition()
{
	/*
		Auto position depending on the button vector
	*/
	for (size_t i = 0; i < mainMenuButtons.size(); ++i)
	{
		if (i == 0)
		{
			mainMenuButtons[i].instance->setPosition({ (500 / 2) - mainMenuButtons[i].instance->getTexture().getWidth() / 2 - 16, leftPanel.bottom().y - mainMenuButtons[i].instance->getTexture().getHeight() - 64 });
		}
		else
		{
			mainMenuButtons[i].instance->setPosition({ mainMenuButtons[i - 1].instance->getX(), mainMenuButtons[i - 1].instance->getY() - mainMenuButtons[i - 1].instance->getTexture().getHeight() - 10 });
		}

		mainMenuButtons[i].instance->setTextColor({ 20, 20, 20, 255 });
		mainMenuButtons[i].instance->getTexture().setColor({ 255, 255, 255, 255 }, true);
		mainMenuButtons[i].instance->setHighlightColor({ 171, 199, 209, 255 });
		mainMenuButtons[i].instance->setAllowAnimation(true);
	}
}

void MainMenu::createMainMenuButtons()
{
	this->hideAccount = false;

	LButton* gameStart = Globals::UI->createButton("gameStart", DEFAULT_BUTTON_TEXTURE);
	LButton* shop = Globals::UI->createButton("shop", DEFAULT_BUTTON_TEXTURE);
	LButton* characterDatabase = Globals::UI->createButton("characterDatabase", DEFAULT_BUTTON_TEXTURE);
	LButton* helpBtn = Globals::UI->createButton("helpBtn", DEFAULT_BUTTON_TEXTURE);
	LButton* gameCredits = Globals::UI->createButton("gameCredits", DEFAULT_BUTTON_TEXTURE);
	LButton* gameQuit = Globals::UI->createButton("gameQuit", DEFAULT_BUTTON_TEXTURE);

	gameStart->supplyCallback(ButtonCallbacks::startGame);
	characterDatabase->supplyCallback(ButtonCallbacks::mainMenuUnitDB);
	gameCredits->supplyCallback(ButtonCallbacks::mainMenuCredits);
	gameQuit->supplyCallback(ButtonCallbacks::quitGame);
	helpBtn->supplyCallback([this]() { this->createHelpButtons(); });
	shop->supplyCallback([this]()
		{
			this->clearButtons();
			OverlayManager::fadeIn(9);
			MusicManager::fadeOutMusic(500);

			Globals::timer->createTimer("shopState", 1.5f, []()
				{
					Globals::engine->createClass("Shop", new Shop);
					Globals::engine->destroyClass("MainMenu");
				}, 1
			);
		}
	);

	mainMenuButtons.push_back({ "gameQuit", gameQuit });
	mainMenuButtons.push_back({ "gameCredits", gameCredits });
	mainMenuButtons.push_back({ "helpBtn", helpBtn });
	mainMenuButtons.push_back({ "characterDatabase", characterDatabase });
	mainMenuButtons.push_back({ "shop", shop });
	mainMenuButtons.push_back({ "gameStart", gameStart });

	this->calculateButtonPosition();

	gameStart->setText("Start");
	shop->setText("Shop");
	characterDatabase->setText("Unit Database");
	helpBtn->setText("Help");
	gameCredits->setText("Credits");
	gameQuit->setText("Exit");
}

void MainMenu::createCreditsButtons()
{
	this->createBackBtn();
	LButton* fbf = Globals::UI->createButton("fbf", DEFAULT_BUTTON_TEXTURE);
	LButton* oj = Globals::UI->createButton("oj", DEFAULT_BUTTON_TEXTURE);
	LButton* deku = Globals::UI->createButton("deku", DEFAULT_BUTTON_TEXTURE);

	deku->supplyCallback(ButtonCallbacks::openLink, "https://music.apple.com/us/artist/deku/657266888");
	oj->supplyCallback(ButtonCallbacks::openLink, "http://daidai.moo.jp/");
	fbf->supplyCallback(ButtonCallbacks::openLink, "https://fruitbatfactory.com/");
	
	mainMenuButtons.push_back({ "fbf", fbf });
	mainMenuButtons.push_back({ "deku", deku });
	mainMenuButtons.push_back({ "oj", oj });

	this->calculateButtonPosition();

	fbf->setText("Fruitbat Factory");
	deku->setText("DEKU");
	oj->setText("Orange_Juice");
}

void MainMenu::createUnitDBButtons()
{
	this->hideAccount = true;
	this->createBackBtn();

	/*
		Create units
	*/

	for (size_t i = 0; i < UnitDefinitions::def.size(); ++i)
	{
		const UnitParams params = UnitDefinitions::def[i];

		LButton* btn = Globals::UI->createButton(params.unitId + "_db_btn", DEFAULT_BUTTON_TEXTURE);
		btn->supplyCallback(ButtonCallbacks::unitDBRequestInfo, params.unitId);
		mainMenuButtons.push_back({ params.unitId + "_db_btn", btn });
		this->calculateButtonPosition();
		btn->setText(params.unitName);
	}
}

void MainMenu::createHelpButtons()
{
	this->clearButtons();
	this->setHeaderTitle("HELP");

	this->createBackBtn();

	LButton* discordHelpBtn = Globals::UI->createButton("discordHelpBtn", DEFAULT_BUTTON_TEXTURE);
	LButton* battleHelpBtn = Globals::UI->createButton("battleHelpBtn", DEFAULT_BUTTON_TEXTURE);
	LButton* panelHelpBtn = Globals::UI->createButton("panelHelpBtn", DEFAULT_BUTTON_TEXTURE);
	LButton* howToHelpBtn = Globals::UI->createButton("howToHelpBtn", DEFAULT_BUTTON_TEXTURE);

	discordHelpBtn->supplyCallback(ButtonCallbacks::openLink, "https://discord.gg/yy6cxwZ");
	battleHelpBtn->supplyCallback([this]() { this->createHelpPicture("assets/help/help3.png"); });
	panelHelpBtn->supplyCallback([this]() { this->createHelpPicture("assets/help/help2.png"); });
	howToHelpBtn->supplyCallback([this]() { this->createHelpPicture("assets/help/help1.png"); });

	mainMenuButtons.push_back({ "discordHelpBtn", discordHelpBtn });
	mainMenuButtons.push_back({ "battleHelpBtn", battleHelpBtn });
	mainMenuButtons.push_back({ "panelHelpBtn", panelHelpBtn });
	mainMenuButtons.push_back({ "howToHelpBtn", howToHelpBtn });

	this->calculateButtonPosition();
	discordHelpBtn->setText("Ask on Discord");
	battleHelpBtn->setText("Battles");
	panelHelpBtn->setText("Panels");
	howToHelpBtn->setText("How to play");
}

LTexture MainMenu::getInformationBar() const
{
	return informationBar;
}

void MainMenu::update(const float dt)
{
	// World layer
	world.render();

	// Unit layer
	mmUnit.render(Globals::engine->getCamera());

	// Top Bar layer
	topBar.render();
	topBarScroll.render();
	topBarScrollLabel.render();

	// Info bar
	informationBar.render();
	informationBarLabel.render();

	// Help Picture
	helpPicture.render();

	// Left panel layer
	leftPanel.render();

	// Account

	if (!hideAccount)
	{
		accountUnit.render({});
		accountName.render();
		accountLevel.render();
		accountStarIcon.render();
		accountStarAmount.render();
	}
	
	// Buttons
	for (size_t i = 0; i < mainMenuButtons.size(); ++i)
	{
		mainMenuButtons[i].instance->render();
	}

	engineVersionLabel.render();
	gameLogo.render();
}