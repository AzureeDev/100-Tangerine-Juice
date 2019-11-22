#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include "LClass.h"
#include "Unit.h"

using std::string;
using std::vector;

struct DisplaySettings { Uint16 w; Uint16 h; Uint16 refreshRate; Uint16 wsWidth; Uint16 wsHeight; };
struct LilacClass { string name; LClass* lilacClass; };

class LilacEngine
{
private:
	string engineVersion = "1.47.0";
	string mainMenuMessage = "Welcome to 100% Tangerine Juice! The update 47 brings a simple Camera.";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = { 0, 0, 1920, 1080 };
	Unit* activeUnit = nullptr;
	DisplaySettings displaySettings = {};
	vector<LilacClass> lilacClasses = {};
	LTexture cursor;

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
	void init();

	void createClass(const string name, LClass* lilacClass);
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