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

shared_ptr<LTextInput> UIManager::createTextInput(const string inputName, const string inputTexturePath)
{
	for (size_t i = 0; i < this->textInputs.size(); ++i)
	{
		if (this->textInputs[i].name == inputName)
		{
			return this->textInputs[i].textInputRef;
		}
	}

	this->textInputs.push_back({ inputName, shared_ptr<LTextInput>(new LTextInput()) });
	this->textInputs.back().textInputRef->init();

	return this->textInputs.back().textInputRef;
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

vector<UIManager::ButtonDefinition> UIManager::getButtons()
{
	return this->buttons;
}

vector<UIManager::TextInputDefinition> UIManager::getTextInputs()
{
	return this->textInputs;
}
