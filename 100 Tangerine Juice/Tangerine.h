#pragma once
#include <vector>
#include <memory>
#include <string>

#include "LClass.h"
#include "World.h"
#include "PlayerUnit.h"
#include "Panel.h"

using std::vector, std::unique_ptr, std::make_unique, std::string;

class Tangerine : public LClass
{
private:
	PlayerUnit test;
	World world;
	vector<unique_ptr<Panel>> panels;
	vector<unique_ptr<PlayerUnit>> units;


public:
	Tangerine();
	~Tangerine();
	void init();
	void update(const float dt);
};

