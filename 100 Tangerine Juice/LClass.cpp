#include "LClass.h"
#include "Globals.h"
#include <SDL.h>

/*
	Lilac Classes

	Based their system on Unity's classes, simply create a derived class based on LClass.
	Constants::game->createLilacClass("classname", new Class);

	init() will be automatically called when the class is created.
	update() is shipped with deltaTime as an argument.

	If you want to get rid of a LClass, call:
	Constants::game->destroyLilacClass("classname");

	The destructor will then be executed.
*/

LClass::LClass(const std::string className, LClass* newClass)
{
	if (newClass == nullptr)
	{
		return;
	}

	this->className = className;
}

LClass::~LClass()
{
}

void LClass::init()
{
}

void LClass::update(const float deltaTime)
{
	for (auto& it : Globals::engine->getLilacClasses())
	{
		if (it.lilacClass == nullptr)
		{
			break;
		}

		it.lilacClass->update(deltaTime);
	}
}

LClass* LClass::getClass(const std::string className)
{
	for (auto& it : Globals::engine->getLilacClasses())
	{
		if (it.lilacClass->getName() == className)
		{
			return it.lilacClass;
		}
	}

	SDL_Log("LClass::getClass() - ERROR : Class %s is not found.", className.c_str());
	return nullptr;
}

std::string LClass::getName()
{
	return this->className;
}