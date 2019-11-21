#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include "LClass.h"
#include "LTexture.h"

using std::string;
using std::vector;

struct DisplaySettings { Uint16 w; Uint16 h; Uint16 refreshRate; Uint16 wsWidth; Uint16 wsHeight; };
struct LilacClass { string name; LClass* lilacClass; };

class LilacEngine
{
private:
	string engineVersion = "1.46.0";
	string mainMenuMessage = "Welcome to 100% Tangerine Juice! The update 46 added a TimerManager, and continued work on the unit card.";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
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

public:
	void init();

	void createClass(const string name, LClass* lilacClass);
	DisplaySettings getDisplaySettings();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	vector<LilacClass> getLilacClasses();
	void destroyClass(const string className);
	string getVersion();
	string getMainMenuMessage();

	void exit();
};