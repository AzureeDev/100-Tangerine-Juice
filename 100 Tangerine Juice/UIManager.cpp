#include "UIManager.h"

LButton* UIManager::createButton(const string btnName, const string btnTexturePath)
{
	this->buttons.push_back({ btnName, make_shared<LButton>(LButton(btnName, btnTexturePath)) });
	
	return this->buttons.back().buttonRef.get();
}

void UIManager::destroyButton(const string btnName)
{
	for (size_t i = 0; i < this->buttons.size(); ++i)
	{
		if (this->buttons[i].name == btnName)
		{
			this->buttons[i].buttonRef.reset();
			this->buttons.erase(this->buttons.begin() + i);

			break;
		}
	}
}

vector<ButtonDefinition> UIManager::getButtons()
{
	return this->buttons;
}
