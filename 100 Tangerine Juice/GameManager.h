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
	vector<shared_ptr<Panel>> map;
	vector<shared_ptr<PlayerUnit>> units;

	/* Debug */
	LButton* restart;

	/* Game variables */
	int currentChapter = 0;
	int currentPlayerTurn = -1;

	/* HUD Messages */
	LTexture messageBg;
	LTexture messageText;

	/* Callback execution */
	void callback(const string id, const function<void()> clbk, const float timer, const int repeat = 1);
	void removeCallback(const string id);

public:
	GameManager(Map& map, Players& units);
	~GameManager();
	void initGame();
	void createHudMessage(const string msg, const float duration = 3.0f);
	shared_ptr<PlayerUnit> getCurrentTurnUnit();
	int getCurrentChapter() const;
	shared_ptr<PlayerUnit> getLocalUnit();
	void nextTurn();
	void gameEnded();
	bool isStandingOnPanel(const int panelId) const;
	void update(const float dt);
};

