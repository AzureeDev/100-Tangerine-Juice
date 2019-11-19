#pragma once
#include <vector>
#include <string>

#include "LClass.h"
#include "LButton.h"
#include "World.h"

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

	LTexture gameLogo;

	LButton* gameStart = nullptr;
	LButton* characterDatabase = nullptr;
	LButton* gameCredits = nullptr;
	LButton* gameQuit = nullptr;

public:
	MainMenu();
	void init();
	void createWorld();
	void createLeftPanel();
	void createTopBar();
	void update(const float dt);
};

