#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
#include "HUDUnit.h"

using std::vector, std::make_shared, std::shared_ptr;

class HUDUnit;

class PlayerUnit : public Unit
{
public:
	enum class UnitStates {
		Idle,
		Moving,
		CustomAnimation
	};

private:
	Uint8 playerId = 0;
	shared_ptr<HUDUnit> hudElement;
	Vector2i initialPosition = { 0, 0 };
	Vector2i destinationPosition = { 0, 0 };
	UnitStates currentState = UnitStates::Idle;
	bool localPlayerUnit = false;
	bool active = false;
	float timer = 0.0f;
	LTexture statusMessage;

protected:
	/* Stats */
	int s_currentHealth = 5;
	int s_maxHealth = 5;
	vector<int> s_stats = {};

	/* Inventory */
	int i_currentStars = 0;
	int i_maxPower = 0;
	int i_currentPower = 0;

	/* Current panel standing on */
	int currentPanel = 0;

public:
	PlayerUnit();
	PlayerUnit(string unitIdentifier);
	~PlayerUnit();
	shared_ptr<HUDUnit> hud();
	void updateHudPosition(const int id);
	void setInitialPosition(const Vector2i& pos);
	void setActiveUnit();
	void setInactiveUnit();
	void setPlayerId(const Uint8 id);
	void setLocalPlayerUnit();
	void setStatusMessage(const string message, const SDL_Color color = { 255, 255, 255, 0 });
	void setCurrentState(const UnitStates state);
	void moveTo(const Vector2i& destination);
	void moveToPanel(int panelId);
	void moveByDiceNb(unsigned int diceNb);
	bool isKO() const;
	virtual void render(SDL_Rect cameraRect);
	int getCurrentHealth() const;
	int getMaxHealth() const;
	vector<int> getStats() const;
	int getCurrentStars() const;
	int getMaxPower() const;
	int getCurrentPower() const;
	int getUnitPanelId() const;
	bool isLocalUnit() const;
	bool isActive() const;
	void playTempAnimation(const string animation, const float duration = 1.f);
	void addPower(const unsigned int amount);
	void addStars(const unsigned int amount);
	void dropStars(const unsigned int amount);

	/* Game state related - turn start ect */
	virtual void startTurn();
	virtual void movement(const int diceRoll);
};
