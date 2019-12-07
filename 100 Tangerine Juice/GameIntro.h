#pragma once
#include <memory>
#include "LClass.h"
#include "Unit.h"
#include "LButton.h"
#include "LTextInput.h"

using std::shared_ptr;

class GameIntro : public LClass
{
private:
	Unit introUnit;
	LTexture gameIntroLabel;
	LButton* introBtn = nullptr;
	shared_ptr<LTextInput> introPlayerNameInput = nullptr;

public:
	GameIntro();
	~GameIntro();
	void init();
	shared_ptr<LTextInput>& getPlayerNameInput();
	void update(const float dt);
};
