#pragma once
#include <vector>
#include <memory>
#include <string>

#include "LClass.h"
#include "World.h"
#include "PlayerUnit.h"
#include "Panel.h"
#include "GameManager.h"

using std::vector, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared, std::string;

class Tangerine : public LClass
{
private:
	PlayerUnit test;
	World world;
	vector<shared_ptr<Panel>> panels;
	vector<shared_ptr<PlayerUnit>> units;
	unique_ptr<GameManager> gameManager;
	float timer = 0.0f;

public:
	Tangerine();
	~Tangerine();
	void init();
	vector<shared_ptr<Panel>>& getMap();
	void update(const float dt);
};

