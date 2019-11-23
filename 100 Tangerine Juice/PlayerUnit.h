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
		Moving
	};

private:
	Uint8 playerId = 0;
	shared_ptr<HUDUnit> hudElement;
	Vector2i initialPosition = { 0, 0 };
	Vector2i destinationPosition = { 0, 0 };
	UnitStates currentState = UnitStates::Idle;
	float timer = 0.0f;

protected:
	/* Stats */
	int s_currentHealth = 5;
	int s_maxHealth = 5;
	vector<int> s_stats = {};

	/* Inventory */
	int i_currentStars = 0;
	int i_maxPower = 0;
	int i_currentPower = 0;

public:
	PlayerUnit();
	PlayerUnit(string unitIdentifier);
	shared_ptr<HUDUnit> hud();
	void updateHudPosition(const int id);
	void setInitialPosition(const Vector2i& pos);
	void setActiveUnit();
	void setPlayerId(const Uint8 id);
	void moveTo(const Vector2i& destination);
	void moveToPanel(const int panelId);
	bool isKO() const;
	virtual void render(SDL_Rect cameraRect);
	int getCurrentHealth() const;
	int getMaxHealth() const;
	vector<int> getStats() const;
	int getCurrentStars() const;
	int getMaxPower() const;
	int getCurrentPower() const;
};

