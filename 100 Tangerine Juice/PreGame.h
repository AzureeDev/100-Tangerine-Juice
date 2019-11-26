#pragma once
#include "LClass.h"
#include "LButton.h"
#include "World.h"
#include <vector>
#include <string>

using std::vector, std::string;

struct UnitPick {
	string unitIdentifier;
	LButton* unitButton = nullptr;
};

struct GameParams {
	enum class WorldGeneration {
		TotalRandom,
		FairRandom,
		Battlefield
	};

	string pickedUnit = "";
	string pickedWorld = "ri_se_sky";
	WorldGeneration pickedGeneration = WorldGeneration::TotalRandom;
};

class PreGame : public LClass
{
private:
	LTexture pregameBg;
	World selectedWorld;
	vector<UnitPick> unitPickButtons = {};
	GameParams gameParameters = {};

	LTexture topBar;
	LTexture topBarScroll;
	LTexture topBarScrollLabel;

	LTexture unitPickedArt;
	Unit unitPicked;

	/* Labels */
	LTexture unitPickLabel;

	bool gameLaunched = false;

public:
	LButton* startGame = nullptr;

	PreGame();
	~PreGame();
	void init();
	void createTopBar();
	void setPickedUnit(const string unitId);
	void onPickedUnit(const string unitPicked);
	void onGameStart();
	GameParams getGameParams() const;
	void update(const float dt);
};
