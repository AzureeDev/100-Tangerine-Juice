#pragma once
#include "LClass.h"
#include "Unit.h"
#include "LButton.h"

enum class DiceComponentType {
	Movement,
	Bonus,
	Drop,
	Recovery
};

class DiceThrowComponent : public LClass
{
private:
	DiceComponentType componentType = DiceComponentType::Movement;
	LTexture componentBgContour;
	LTexture componentBg;
	LTexture componentBgText;
	LTexture componentText;
	LTexture componentDiceText;
	LTexture componentDiceTexture;
	Unit componentUnit;
	LButton* componentButton = nullptr;

public:
	DiceThrowComponent(const bool isAI = false, const DiceComponentType type = DiceComponentType::Movement);
	~DiceThrowComponent();
	void init();
	void onPress();
	void update(const float dt);
};
