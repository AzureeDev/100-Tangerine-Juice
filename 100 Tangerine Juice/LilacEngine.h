#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include "LClass.h"
#include "Unit.h"

using std::string;
using std::vector;

struct DisplaySettings { int w; int h; int refreshRate; int wsWidth; int wsHeight; };
struct LilacClass { string name; LClass* lilacClass; };

class LilacEngine
{
private:
	string engineVersion = "1.53.0";
	string mainMenuMessage = "Welcome to 100% Tangerine Juice! Hope you will enjoy your time here. ~";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = { 0, 0, 1920, 1080 };
	Unit* activeUnit = nullptr;
	Unit* currentActiveUnit = nullptr;
	DisplaySettings displaySettings = {};
	vector<LilacClass> lilacClasses = {};
	LTexture cursor;
	float timer = 0.0f;
	bool running = true;

private:
	void createWindow();
	void initGlobals();
	void initBaseResources();
	void initBaseClasses();
	void update();
	void destroyClasses();
	void checkBackButton();

public:
	float GLOBAL_DELTA_TIME = 0.0f;

	void init();

	void createClass(const string name, LClass* lilacClass);
	bool hasClass(const string name) const;
	DisplaySettings getDisplaySettings();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	SDL_Rect getCamera();
	void setActiveCameraUnit(Unit* newUnit);
	vector<LilacClass> getLilacClasses();
	void destroyClass(const string className);
	string getVersion();
	string getMainMenuMessage();

	void exit();
};