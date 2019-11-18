#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SDL.h>
#include "LClass.h"

using std::string;
using std::vector;

struct DisplaySettings { Uint16 w; Uint16 h; Uint16 refreshRate; };
struct LilacClass { string name; LClass* lilacClass; };

class LilacEngine
{
private:
	string engineVersion = "1.42.0";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	DisplaySettings displaySettings = {};
	vector<LilacClass> lilacClasses = {};

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

	LClass* createClass(const string name, LClass* lilacClass);

	DisplaySettings getDisplaySettings();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	vector<LilacClass> getLilacClasses();

	void exit();
};