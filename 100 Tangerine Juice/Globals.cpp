#include "Globals.h"

/*
	Globals
*/

// Init global variables
int Globals::mousePositionX = 0;
int Globals::mousePositionY = 0;

// Init pointers to nullptr
LilacEngine* Globals::engine = nullptr; 
unique_ptr<ResourcesManager> Globals::resources = nullptr; 
unique_ptr<LClass> Globals::classEngine = nullptr;
unique_ptr<UIManager> Globals::UI = nullptr;
unique_ptr<TimerManager> Globals::timer = nullptr;

/*
	LilacClasses
*/

GameIntro* LilacClasses::GameIntro = nullptr; 
MainMenu* LilacClasses::MainMenu = nullptr; 
PreGame* LilacClasses::PreGame = nullptr;
Tangerine* LilacClasses::Tangerine = nullptr;