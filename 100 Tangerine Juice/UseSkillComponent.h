#pragma once
#include "LClass.h"
#include "LButton.h"
#include <vector>
#include <memory>
#include "SkillDefinitions.h"

using std::vector, std::shared_ptr;

class UseSkillComponent : public LClass
{
public:
	enum class GameState {
		OutBattle,
		InBattle
	};

private:
	struct SkillButtonDef {
		string skillIdentifier;
		shared_ptr<LTexture> skillIcon = nullptr;
		shared_ptr<LTexture> skillName = nullptr;
		shared_ptr<LTexture> skillDesc = nullptr;
		shared_ptr<LTexture> skillPwrIcon = nullptr;
		shared_ptr<LTexture> skillPwrAmount = nullptr;
		shared_ptr<LButton> skillBtn = nullptr;
	};
	
	LTexture componentBg;
	LButton* componentBack = nullptr;
	LTexture componentTotalPwrIcon;
	LTexture componentTotalPwrAmount;
	vector<SkillButtonDef> skillButtons = {};
	GameState componentGameState = GameState::OutBattle;

public:
	UseSkillComponent(const GameState currentState);
	~UseSkillComponent();
	void init();
	void generateSkillButtons();
	void checkSkillAvailability(shared_ptr<LTexture>& skillNamePtr, shared_ptr<LTexture>& skillDescPtr, shared_ptr<LButton>& skillBtnPtr, SkillData& skillData);
	void useSkill(string skillIdentifier);
	void destroyComponent();
	void update(const float dt);
};

