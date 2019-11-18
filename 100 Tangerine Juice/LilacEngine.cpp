// Base Libraries
#include <ctime>
#include <cstdlib>

// Include SDL Libraries
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "LilacEngine.h"
#include "Globals.h"
#include "GameIntro.h"

// Define the window and renderer
void LilacEngine::createWindow()
{
	// Get the display size
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	// And set them
	this->displaySettings.w = dm.w;
	this->displaySettings.h = dm.h;
	this->displaySettings.refreshRate = dm.refresh_rate;

	// Base workspace size
	const Uint16 workspaceWidth = 1920;
	const Uint16 workspaceHeight = 1080;

	// Create the window
	this->window = SDL_CreateWindow(
		"PROJECT ZERO",
		this->displaySettings.w / 2 - workspaceWidth / 2,
		this->displaySettings.h / 2 - workspaceHeight / 2,
		workspaceWidth,
		workspaceHeight,
		SDL_WINDOW_BORDERLESS
	);

	// Create the renderer
	this->renderer = SDL_CreateRenderer(
		this->window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
}

// Init global pointers to core resources
void LilacEngine::initGlobals()
{
	Globals::engine = this;
	Globals::resources = std::make_unique<ResourcesManager>(ResourcesManager());
	Globals::classEngine = std::make_unique<LClass>(LClass("", nullptr));
}

void LilacEngine::initBaseResources()
{
	// Fonts
	Globals::resources->createFont("defaultFontTiny", "assets/fonts/sofia.otf", 11);
	Globals::resources->createFont("defaultFontSmall", "assets/fonts/sofia.otf", 16);
	Globals::resources->createFont("defaultFont", "assets/fonts/sofia.otf", 24);
	Globals::resources->createFont("defaultFontLarge", "assets/fonts/sofia.otf", 48);
}

void LilacEngine::initBaseClasses()
{
	this->createClass("GameIntro", new GameIntro);
}

// Main game loop
void LilacEngine::update()
{
	// Define variables to get a solid deltatime
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;

	// Main loop defined here
	while (this->running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EventType::SDL_MOUSEMOTION:
				SDL_GetMouseState(&Globals::mousePositionX, &Globals::mousePositionY);
				break;

			case SDL_EventType::SDL_QUIT:
				this->exit();
				break;

			case SDL_EventType::SDL_MOUSEBUTTONDOWN:
				/*for (auto uiBtnIt : Constants::uiManager->allButtons())
				{
					if (uiBtnIt.second->isMouseInside() && uiBtnIt.first == uiBtnIt.second->getId())
					{
						if (uiBtnIt.second->isEnabled())
						{
							uiBtnIt.second->event(event);
							break;
						}
					}
				}*/
				break;
			}
		}

		// DeltaTime
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) / (float)SDL_GetPerformanceFrequency());

		SDL_RenderClear(this->renderer);
		Globals::classEngine->update(deltaTime);
		SDL_RenderPresent(this->renderer);
	}
}

void LilacEngine::destroyClasses()
{
	for (size_t i = 0; i < this->lilacClasses.size(); ++i)
	{
		delete this->lilacClasses[i].lilacClass;
		this->lilacClasses[i].lilacClass = nullptr;
		this->lilacClasses.erase(this->lilacClasses.begin() + i);
	}
}

// Initialize the game engine with all the SDL modules we need
void LilacEngine::init()
{
	// Init Rand()
	srand((unsigned int)time(NULL));
	// Init SDL with the following modules
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO);
	// SDL Hints
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	// Init extra modules
	TTF_Init();
	IMG_Init(IMG_InitFlags::IMG_INIT_PNG);
	Mix_Init(MIX_InitFlags::MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// Create the window and renderer
	this->createWindow();

	// Init global pointers
	this->initGlobals();

	// Init base resources
	this->initBaseResources();

	// Init the base classes
	this->initBaseClasses();

	// And initiate our game loop
	this->update();
}

// Create a new LClass, which is automatically initialized. Returns the created class.
LClass* LilacEngine::createClass(const string name, LClass* lilacClass)
{
	LilacClass classDef = { name, lilacClass };
	this->lilacClasses.push_back(classDef);

	lilacClass->init();

	return lilacClass;
}

DisplaySettings LilacEngine::getDisplaySettings()
{
	return this->displaySettings;
}

SDL_Renderer* LilacEngine::getRenderer()
{
	return this->renderer;
}

SDL_Window* LilacEngine::getWindow()
{
	return this->window;
}

vector<LilacClass> LilacEngine::getLilacClasses()
{
	return this->lilacClasses;
}

// On quit, quit all SDL modules and extra classes that need a cleanup
void LilacEngine::exit()
{
	this->running = false;

	this->destroyClasses();
	Globals::resources->destroy();

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}
