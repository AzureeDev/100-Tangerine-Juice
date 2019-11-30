#include "UIManager.h"

LButton* UIManager::createButton(const string btnName, const string btnTexturePath)
{
	for (size_t i = 0; i < this->buttons.size(); ++i)
	{
		if (this->buttons[i].name == btnName)
		{
			this->buttons[i].buttonRef->setVisible(true);
			this->buttons[i].buttonRef->setEnabled(true);

			return this->buttons[i].buttonRef.get();
		}
	}

	this->buttons.push_back({ btnName, shared_ptr<LButton>(new LButton(btnName, btnTexturePath)) });
	return this->buttons.back().buttonRef.get();
}

shared_ptr<LButton> UIManager::createSharedButton(const string btnName, const string btnTexturePath)
{
	for (size_t i = 0; i < this->buttons.size(); ++i)
	{
		if (this->buttons[i].name == btnName)
		{
			this->buttons[i].buttonRef->setVisible(true);
			this->buttons[i].buttonRef->setEnabled(true);

			return this->buttons[i].buttonRef;
		}
	}

	this->buttons.push_back({ btnName, shared_ptr<LButton>(new LButton(btnName, btnTexturePath)) });
	return this->buttons.back().buttonRef;
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