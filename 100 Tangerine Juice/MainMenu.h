#pragma once
#include <vector>
#include <string>

#include "LClass.h"
#include "LButton.h"
#include "World.h"
#include "UnitCardComponent.h"

using std::vector;
using std::string;

class MainMenu : public LClass
{
private:
	World world;

	LTexture engineVersionLabel;
	LTexture leftPanel;
	LTexture topBar;
	LTexture topBarScroll;
	LTexture topBarScrollLabel;
	LTexture informationBar;
	LTexture informationBarLabel;
	LTexture helpPicture;

	LTexture gameLogo;

	// Structs for the vectors below
	typedef struct { string name; LButton* instance; } MainMenuButtonDefinition;

	vector<MainMenuButtonDefinition> mainMenuButtons = {};

public:
	Unit mmUnit;

	MainMenu();
	~MainMenu();
	void init();
	void createWorld();
	void createFwdUnits();
	void createLeftPanel();
	void createTopBar();
	void createInformationBar();
	void createHelpPicture(const string helpPictureTexture);
	void hideHelpPicture();
	void createBackBtn();
	void setHeaderTitle(const string newTitle);

	void clearButtons();
	void calculateButtonPosition();
	void createMainMenuButtons();
	void createCreditsButtons();
	void createUnitDBButtons();
	void createHelpButtons();

	LTexture getInformationBar() const;

	void update(const float dt);
};
