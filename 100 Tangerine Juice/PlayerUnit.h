#pragma once
#include <vector>
#include <memory>
#include "Unit.h"
#include "HUDUnit.h"
#include "UnitDefinitions.h"
#include "LButton.h"

using std::vector, std::make_shared, std::shared_ptr;

class HUDUnit;
class SkillDefinition;
struct SkillData;

class PlayerUnit : public Unit
{
public:
	enum class UnitStates {
		Idle,
		Moving,
		CustomAnimation
	};

	enum class UnitDefenseType {
		Defense,
		Evasion
	};

	struct ActiveSkill {
		string skillIdentifier;
		int skillDuration = 0;
		int skillStack = 0;
	};

private:
	Uint8 playerId = 0;
	shared_ptr<HUDUnit> hudElement = nullptr;
	Vector2i initialPosition = { 0, 0 };
	Vector2i destinationPosition = { 0, 0 };
	UnitStates currentState = UnitStates::Idle;
	bool localPlayerUnit = false;
	bool active = false;
	float timer = 0.0f;
	LTexture statusMessage;

	/* Begin turn buttons */
	LButton* moveBtn = nullptr;
	LButton* skillBtn = nullptr;

protected:
	/* Stats */
	int s_currentHealth = 5;
	int s_maxHealth = 5;
	int s_currentRecovery = 0;
	vector<int> s_stats = {};
	vector<int> s_tempStats = { 0, 0, 0, 0, 0, 0 };

	/* Inventory */
	int i_currentStars = 0;
	int i_maxPower = 0;
	int i_currentPower = 0;

	/* Current panel standing on */
	int currentPanel = 0;
	
	/* All skills */
	vector<SkillData> unitSkills = {};
	vector<ActiveSkill> currentSkills = {};

public:
	PlayerUnit();
	PlayerUnit(string unitIdentifier);
	~PlayerUnit();
	shared_ptr<HUDUnit> hud();
	void destroyTurnButtons();
	void activateTurnButtons();
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
	virtual bool isAI() const;
	bool isKO() const;
	string getName();
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
	void beginMovementRoll();
	void addPower(const unsigned int amount);
	void removePower(const unsigned int amount);
	void addStars(const unsigned int amount);
	void dropStars(const unsigned int amount);
	void heal(const int amount);
	int takeDamage(const int attackRoll, const int defenseRoll, const UnitDefenseType defenseType);
	void onKO();
	int getCurrentRecovery();
	void decreaseRecovery();
	void revive();
	void onRevived();
	void createSkillEffect(const ActiveSkill activeSkillData);
	bool hasSkillEffect(const string skillIdentifier);
	int getCurrentStackForEffect(const string skillIdentifier);
	void updateSkillEffect();
	void onTurnStart();

	/* Game state related - turn start ect */
	virtual void startTurn();
	virtual void movement(const int diceRoll);

	/* Stat retrieve (with boosts) */
	int getAttackStat() const;
	int getDefenseStat() const;
	int getEvasionStat() const;

	/* Skill data */
	vector<SkillData> getSkills() const;

	/* Final Render */
	virtual void render(SDL_Rect cameraRect);
};
