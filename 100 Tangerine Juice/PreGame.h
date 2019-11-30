#pragma once
#include "LClass.h"
#include "LButton.h"
#include "World.h"
#include "UnitDefinitions.h"
#include <vector>
#include <string>
#include <memory>

using std::vector, std::string, std::shared_ptr;

/* Used to initialize Tangerine */
struct GameParams {
	enum class WorldGeneration {
		TotalRandom,
		FairRandom,
		Battlefield
	};

	string pickedUnit = "";
	string pickedWorld = "ri_se_sky";
	WorldGeneration pickedGeneration = WorldGeneration::FairRandom;
};

class PreGame : public LClass
{
private:

	/* Unit buttons */
	struct UnitPick {
		string unitIdentifier;
		LButton* unitButton = nullptr;
	};

	/* World gen buttons */
	struct WorldGenPick {
		GameParams::WorldGeneration worldGeneration;
		LButton* worldGenButton = nullptr;
	};

	/* Struct to render a skill */
	struct Skill {
		string skillIcon = "";
		string skillName = "";
		string skillDesc = "";
		int skillCost = 0;
		vector<shared_ptr<LTexture>> skillTextures = {};
	};

	/* World, bg & params */
	LTexture pregameBg;
	World selectedWorld;
	vector<UnitPick> unitPickButtons = {};
	vector<WorldGenPick> worldGenPickButtons = {};
	GameParams gameParameters = {};
	vector<Skill> unitSkills = {};

	/* Top bar */
	LTexture topBar;
	LTexture topBarScroll;
	LTexture topBarScrollLabel;

	/* Unit picked art */
	LTexture unitPickedArt;
	Unit unitPicked;

	/* Labels */
	LTexture labelBar;
	LTexture unitPickLabel;
	LTexture unitNameLabel;
	LTexture unitSkillLabel;
	LTexture worldGenerationLabel;

	/* Stats */
	LTexture unitHPLabel;
	LTexture unitHPAmount;
	LTexture unitAtkLabel;
	LTexture unitAtkAmount;
	LTexture unitDefLabel;
	LTexture unitDefAmount;
	LTexture unitEvaLabel;
	LTexture unitEvaAmount;
	LTexture unitRecLabel;
	LTexture unitRecAmount;
	LTexture unitPwrLabel;
	LTexture unitPwrEffect;
	LTexture unitPwrAmount;

	/* Buttons */
	LButton* startGame = nullptr;
	LButton* worldGenRandom = nullptr;
	LButton* worldGenFairRandom = nullptr;
	LButton* worldGenBattlefield = nullptr;

	bool gameLaunched = false;

public:
	PreGame();
	~PreGame();
	void init();
	void createTopBar();
	void setPickedUnit(const string unitId);
	void setPickedWorldGen(const GameParams::WorldGeneration worldGen);
	void onPickedUnit(const string& unitId);
	void createStats(const string& unitId);
	void createSkills(const UnitParams& params);
	void createWorldOptions();
	void onGameStart();
	GameParams getGameParams() const;
	void update(const float dt);
};
