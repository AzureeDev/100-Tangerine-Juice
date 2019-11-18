#pragma once
#include <string>
#include <vector>
#include <memory>
#include "LButton.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;

struct ButtonDefinition { string name; shared_ptr<LButton> buttonRef; };
class UIManager
{
private:
	vector<ButtonDefinition> buttons = {};

public:
	LButton* createButton(const string btnName, const string btnTexturePath = "assets/ui/transparent.png");
	vector<ButtonDefinition> getButtons();
};

