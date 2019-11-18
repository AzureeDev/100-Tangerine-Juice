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
	Globals::engine->destroyLilacClass("name");

	The destructor will then be executed.
*/

LClass::LClass(LClass* newClass)
{
	if (newClass == nullptr)
	{
		return;
	}
}

LClass::~LClass()
{
	/*
		Virtual destructor, define one in the LClasses themselves.
	*/
}

void LClass::init()
{
	/*
		Init is automatically called when you create the LClass.
	*/
}

void LClass::update(const float deltaTime)
{
	/*
		Updated once per frame, shipping the deltaTime.
	*/

	for (auto& it : Globals::engine->getLilacClasses())
	{
		if (it.lilacClass == nullptr)
		{
			break;
		}

		it.lilacClass->update(deltaTime);
	}
}