#pragma once
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "Panel.h"
#include "PlayerUnit.h"
#include "LButton.h"

using std::vector, std::shared_ptr, std::make_shared, std::string, std::function;

typedef vector<shared_ptr<Panel>> Map;
typedef vector<shared_ptr<PlayerUnit>> Players;

class GameManager
{
private:
	vector<shared_ptr<Panel>> map = {};
	vector<shared_ptr<PlayerUnit>> units = {};

	/* Debug */
	LButton* restart = nullptr;
	LButton* mainMenu = nullptr;

	/* Game variables */
	int currentChapter = 0;
	int currentPlayerTurn = -1;

	/* HUD Messages */
	LTexture messageBg;
	LTexture messageText;

	/* Ending bg */
	LTexture endingFade;

	/* Callback execution */
	void callback(const string id, const function<void()> clbk, const float timer, const int repeat = 1);
	void removeCallback(const string id);

public:
	struct BattleSkillParams {
		string attackerSkill = "";
		string defenderSkill = "";
		shared_ptr<PlayerUnit> attackerUnit = nullptr;
		shared_ptr<PlayerUnit> defenderUnit = nullptr;
		Unit& attackerBattleUnit;
		Unit& defenderBattleUnit;
	};

	GameManager(Map& map, Players& units);
	~GameManager();
	void initGame();
	void createHudMessage(const string msg, const float duration = 3.0f);
	vector<shared_ptr<PlayerUnit>> getUnits();
	shared_ptr<PlayerUnit> getCurrentTurnUnit();
	shared_ptr<PlayerUnit> getRandomUnitExcluding(const shared_ptr<PlayerUnit> exclusion);
	shared_ptr<PlayerUnit> getRandomAliveUnitExcluding(const shared_ptr<PlayerUnit> exclusion);
	UnitParams getCurrentUnitParams();
	int getCurrentChapter() const;
	shared_ptr<PlayerUnit> getLocalUnit();
	shared_ptr<PlayerUnit> getUnitByIdentifier(const string identifier);
	unsigned getAliveUnitsCount() const;
	void nextTurn();
	void gameEnded();
	bool isStandingOnPanel(const int panelId) const;
	void useSkill(const string skillIdentifier);
	void update(const float dt);
};
