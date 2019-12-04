#pragma once
#include "LClass.h"
#include "PlayerUnit.h"
#include <memory>
#include <vector>

using std::shared_ptr, std::vector;

struct PlayerItem {
	Unit playerUnit;
	shared_ptr<PlayerUnit> playerPtr;
	vector<shared_ptr<LTexture>> itemTextures;
};

class EndgameComponent : public LClass
{
private:
	LTexture componentBg;
	LTexture componentWinnerLabel;
	LTexture componentExitLabel;
	LButton* componentExitBtn = nullptr;
	LTexture winnerName;
	vector<PlayerItem> playerItems = {};
	bool allowRenderUnits = false;

public:
	EndgameComponent();
	~EndgameComponent();
	void init();
	void createPlayerItems();
	void onExitPressed();
	void update(const float dt);
};

