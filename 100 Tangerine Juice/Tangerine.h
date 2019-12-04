#pragma once
#include <vector>
#include <memory>
#include <string>

#include "LClass.h"
#include "World.h"
#include "PlayerUnit.h"
#include "Panel.h"
#include "GameManager.h"
#include "PreGame.h"

using std::vector, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared, std::string;

class Tangerine : public LClass
{
private:
	PlayerUnit test;
	World world;
	GameParams gameParams;
	vector<shared_ptr<Panel>> panels;
	vector<shared_ptr<PlayerUnit>> units;
	unique_ptr<GameManager> gameManager;
	float timer = 0.0f;

public:
	Tangerine(GameParams params);
	~Tangerine();
	void init();
	vector<shared_ptr<Panel>>& getMap();
	unique_ptr<GameManager>& getGameManager();
	GameParams& getGameParams();
	void update(const float dt);
	World& getWorld();
};
