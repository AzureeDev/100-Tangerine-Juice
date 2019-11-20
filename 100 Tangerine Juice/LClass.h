#pragma once
#include <string>

/* Common includes for LClasses below */
#include "LTexture.h"

class LClass
{
protected:
	std::string className;

public:
	LClass();
	virtual ~LClass();
	virtual void init();
	virtual void update(const float deltaTime);
};