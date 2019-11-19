#pragma once
#include "LClass.h"
#include "Unit.h"
#include "LButton.h"

class GameIntro : public LClass
{
private:
	Unit introUnit;
	LTexture gameIntroLabel;
	LButton* introBtn;

public:
	GameIntro();
	~GameIntro();
	void init();
	void update(const float dt);
};

