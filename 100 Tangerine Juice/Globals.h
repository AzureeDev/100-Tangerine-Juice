#pragma once
#include <memory>

/* Globals */
#include "LilacEngine.h"
#include "ResourcesManager.h"
#include "UIManager.h"
#include "LClass.h"
#include "TimerManager.h"
#include "GameManager.h"

using std::unique_ptr;

struct Globals
{
	// Global Variables
	static int mousePositionX;
	static int mousePositionY;

	// Ptr to classes
	static LilacEngine* engine;
	static unique_ptr<ResourcesManager> resources;
	static unique_ptr<UIManager> UI;
	static unique_ptr<LClass> classEngine;
	static unique_ptr<TimerManager> timer;
	static GameManager* gameManager;
};

/* LilacClasses */
#include "GameIntro.h"
#include "MainMenu.h"
#include "PreGame.h"
#include "Tangerine.h"

struct LilacClasses
{
	static GameIntro* GameIntro;
	static MainMenu* MainMenu;
	static PreGame* PreGame;
	static Tangerine* Tangerine;
};
