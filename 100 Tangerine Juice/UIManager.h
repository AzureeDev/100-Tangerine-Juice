#pragma once
#include <string>
#include <vector>
#include <memory>
#include "LButton.h"
#include "LTextInput.h"

using std::string, std::vector, std::shared_ptr;

class UIManager
{
	struct ButtonDefinition { string name; shared_ptr<LButton> buttonRef = nullptr; };
	struct TextInputDefinition { string name; shared_ptr<LTextInput> textInputRef = nullptr; };
	vector<ButtonDefinition> buttons = {};
	vector<TextInputDefinition> textInputs = {};

public:
	LButton* createButton(const string btnName, const string btnTexturePath = "assets/ui/transparent.png");
	shared_ptr<LButton> createSharedButton(const string btnName, const string btnTexturePath = "assets/ui/transparent.png");
	shared_ptr<LTextInput> createTextInput(const string inputName, const string inputTexturePath = "assets/ui/rect_base.png");
	void destroyButton(const string btnName);
	vector<UIManager::ButtonDefinition> getButtons();
	vector<UIManager::TextInputDefinition> getTextInputs();
};
