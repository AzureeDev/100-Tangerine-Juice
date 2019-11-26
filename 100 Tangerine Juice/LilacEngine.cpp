// Base Libraries
#include <ctime>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

// Include SDL Libraries
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Include our headers
#include "LilacEngine.h"
#include "Globals.h"
#include "GameIntro.h"
#include "OverlayManager.h"

void LilacEngine::createWindow()
{
	/*
		Define the window and renderer
	*/

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

	this->displaySettings.wsWidth = workspaceWidth;
	this->displaySettings.wsHeight = workspaceHeight;

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

	// Hide the mouse cursor (got a custom one.)
	SDL_ShowCursor(false);
}

void LilacEngine::initGlobals()
{
	/*
		Init global pointers to core resources
	*/

	Globals::engine = this;
	Globals::resources = std::make_unique<ResourcesManager>(ResourcesManager());
	Globals::UI = std::make_unique<UIManager>(UIManager());
	Globals::classEngine = std::make_unique<LClass>(LClass());
	Globals::timer = std::make_unique<TimerManager>(TimerManager());
}

void LilacEngine::initBaseResources()
{
	/*
		Initiate base resources for the game to work.
	*/

	// Fonts
	Globals::resources->createFont("defaultFontTiny", "assets/fonts/sofia.otf", 11);
	Globals::resources->createFont("defaultFontSmall", "assets/fonts/sofia.otf", 16);
	Globals::resources->createFont("defaultFont", "assets/fonts/sofia.otf", 24);
	Globals::resources->createFont("defaultFont27", "assets/fonts/sofia.otf", 27);
	Globals::resources->createFont("defaultFont32", "assets/fonts/sofia.otf", 32);
	Globals::resources->createFont("defaultFontLarge", "assets/fonts/sofia.otf", 48);

	Globals::resources->createFont("bleachFont", "assets/fonts/bleach_fixed.ttf", 24);
	Globals::resources->createFont("bleachFontMedium", "assets/fonts/bleach_fixed.ttf", 36);
	Globals::resources->createFont("bleachFontLarge", "assets/fonts/bleach_fixed.ttf", 54);

	Globals::resources->createFont("qeFont", "assets/fonts/qe.ttf", 24);

	this->cursor.setNewTexture("assets/ui/cursor.png");

	// Sprites
	string spriteBasePath = "assets/units";

	for (const auto& dir : fs::directory_iterator(spriteBasePath))
	{
		for (const auto& sprite : fs::directory_iterator(dir.path().generic_string().c_str()))
		{
			Globals::resources->createTexture(sprite.path().generic_string());
		}
	}
}

void LilacEngine::initBaseClasses()
{
	this->createClass("GameIntro", new GameIntro);
}

void LilacEngine::update()
{
	/*
		Main game loop
	*/

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

			case SDL_EventType::SDL_KEYDOWN:

				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					this->checkBackButton();
					break;
				}

				break;

			case SDL_EventType::SDL_MOUSEBUTTONDOWN:
				for (const auto& uiBtnIt : Globals::UI->getButtons())
				{
					if (uiBtnIt.buttonRef->isMouseInside() && uiBtnIt.name == uiBtnIt.buttonRef->getId())
					{
						if (uiBtnIt.buttonRef->isEnabled())
						{
							uiBtnIt.buttonRef->event(event);
							break;
						}
					}
				}
				break;
			}
		}

		// DeltaTime
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) / (float)SDL_GetPerformanceFrequency());

		timer += deltaTime;

		this->GLOBAL_DELTA_TIME = deltaTime;

		SDL_RenderClear(this->renderer);

		// TimerManager update.
		Globals::timer->update(deltaTime);

		// LClass updates.
		Globals::classEngine->update(deltaTime);

		// Camera update on a active unit
		if (this->activeUnit != nullptr)
		{
			Vector2i vecCamera = { this->camera.x, this->camera.y };
#pragma warning( push )
#pragma warning( disable : 4244)
			this->camera.x = vecCamera.lerp({ (this->activeUnit->position().x + 256) - (Globals::engine->getDisplaySettings().wsWidth / 2), 0 }, this->timer).x;
#pragma warning( pop )
			this->camera.y = this->activeUnit->position().y - (Globals::engine->getDisplaySettings().wsHeight / 2);
		}

		if (this->camera.x < 0) { this->camera.x = 0; }
		if (this->camera.y < 0) { this->camera.y = 0; }

		// Cursor pos and render, always on top
		this->cursor.setPosition({ Globals::mousePositionX, Globals::mousePositionY });
		this->cursor.render();

		OverlayManager::update(deltaTime);

		SDL_RenderPresent(this->renderer);
	}
}

void LilacEngine::destroyClasses()
{
	/*
		Destroy all loaded classes
	*/

	for (size_t i = 0; i < this->lilacClasses.size(); ++i)
	{
		delete this->lilacClasses[i].lilacClass;
		this->lilacClasses[i].lilacClass = nullptr;
		this->lilacClasses.erase(this->lilacClasses.begin() + i);
	}
}

void LilacEngine::checkBackButton()
{
	// If a generic back button exists, execute it if escape is pressed.

	for (const auto& button : Globals::UI->getButtons())
	{
		if (button.name == "back")
		{
			button.buttonRef->executeCallback();
		}
	}
}

void LilacEngine::init()
{
	/*
		Initialize the game engine with all the SDL modules we need
	*/

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

	// Init OverlayManager
	OverlayManager::init();

	// Init Definitions
	UnitDefinitions::createDefinitions();

	SDL_Log("Initialized. Starting the main loop...");

	// And initiate our game loop
	this->update();
}

void LilacEngine::createClass(const string name, LClass* lilacClass)
{
	/*
		Create a new LClass, which is automatically initialized. Returns the created class.
	*/

	LilacClass classDef = { name, lilacClass };
	this->lilacClasses.push_back(classDef);

	lilacClass->init();
}

bool LilacEngine::hasClass(const string name) const
{
	for (const auto& lclass : this->lilacClasses)
	{
		if (lclass.name == name)
		{
			return true;
		}
	}

	return false;
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

SDL_Rect LilacEngine::getCamera()
{
	return this->camera;
}

void LilacEngine::setActiveCameraUnit(Unit* newUnit)
{
	this->timer = 0.0f;
	this->activeUnit = newUnit;
}

vector<LilacClass> LilacEngine::getLilacClasses()
{
	return this->lilacClasses;
}

void LilacEngine::destroyClass(const string className)
{
	/*
		Destroy a single LClass by name
	*/

	for (size_t i = 0; i < this->lilacClasses.size(); ++i)
	{
		if (this->lilacClasses[i].name == className)
		{
			delete this->lilacClasses[i].lilacClass;
			this->lilacClasses[i].lilacClass = nullptr;
			this->lilacClasses.erase(this->lilacClasses.begin() + i);

			break;
		}
	}
}

string LilacEngine::getVersion()
{
	return this->engineVersion;
}

string LilacEngine::getMainMenuMessage()
{
	return this->mainMenuMessage;
}

void LilacEngine::exit()
{
	/*
		On quit, quit all SDL modules and extra classes that need a cleanup
	*/

	this->running = false;

	this->destroyClasses();
	Globals::resources->destroy();
	OverlayManager::destroy();

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}