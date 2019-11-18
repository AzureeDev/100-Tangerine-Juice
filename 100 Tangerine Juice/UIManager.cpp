#include "UIManager.h"

LButton* UIManager::createButton(const string btnName, const string btnTexturePath)
{
	this->buttons.push_back({ btnName, make_shared<LButton>(LButton(btnName, btnTexturePath)) });
	
	return this->buttons.back().buttonRef.get();
}

vector<ButtonDefinition> UIManager::getButtons()
{
	return this->buttons;
}
