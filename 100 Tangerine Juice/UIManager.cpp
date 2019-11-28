#include "UIManager.h"

LButton* UIManager::createButton(const string btnName, const string btnTexturePath)
{
	this->buttons.push_back({ btnName, shared_ptr<LButton>(new LButton(btnName, btnTexturePath)) });

	return this->buttons.back().buttonRef.get();
}

void UIManager::destroyButton(const string btnName)
{
	for (size_t i = 0; i < this->buttons.size(); ++i)
	{
		if (this->buttons[i].name == btnName)
		{	
			this->buttons[i].buttonRef.reset();
			this->buttons[i].buttonRef = nullptr;
			this->buttons.erase(this->buttons.begin() + i);

			return;
		}
	}

	SDL_Log("UIManager::destroyButton() : Couldn't destroy the button %s : it wasn't found.", btnName.c_str());
}

vector<ButtonDefinition> UIManager::getButtons()
{
	return this->buttons;
}