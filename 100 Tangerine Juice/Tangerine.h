#pragma once
#include "LClass.h"
#include "World.h"
#include "PlayerUnit.h"

class Tangerine : public LClass
{
private:
	PlayerUnit test;
	PlayerUnit test2;
	World world;

public:
	Tangerine();
	~Tangerine();
	void init();
	void update(const float dt);
};

