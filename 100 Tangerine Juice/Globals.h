#pragma once
#include <memory>
#include "LilacEngine.h"
#include "ResourcesManager.h"
#include "UIManager.h"
#include "LClass.h"

using std::unique_ptr;

class Globals
{
public:
	// Global Variables
	static int mousePositionX;
	static int mousePositionY;

	// Ptr to classes
	static LilacEngine* engine;
	static unique_ptr<ResourcesManager> resources;
	static unique_ptr<UIManager> UI;
	static unique_ptr<LClass> classEngine;
};

