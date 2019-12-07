#pragma once
#include <string>
#include <vector>
#include "LTexture.h"
#include "LButton.h"

using std::string, std::vector;

class LTextInput
{
private:
	bool moduleActive = false;	// if the module is clicked on, ready to receive text
	unsigned moduleCharacterLimit = 15; // how much characters we accept
	bool moduleEnabled = true;	// if the module can be clicked at all
	string moduleText = "";		// final built up text
	string modulePlaceholderText = "";	// placeholder text if no usertext is there
	vector<string> moduleTextContainer = {};	// vector that holds each single characters, which is later constructed in moduleText
	LTexture moduleBackground; // background of the module
	LTexture moduleTextTexture; // final texture of the text we entered
	LTexture moduleTextVerticalBar; // vertical bar saying the input is ready to get text
	Vector2i modulePosition = { 0, 0 }; // Module pos
	vector<string> moduleAllowedCharacters = {
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"*", "/", "'", "\"", "-", "_", "&", "(", ")", "[", "]", "{", "}"
	}; // Allowed characters for the input

public:
	LTextInput();
	~LTextInput();
	void init();
	void onModuleClick();
	void onBackspacePress();
	void onKeyPress(string& character);
	void buildString();
	bool isMouseInside() const;
	LTexture& getVerticalBar();
	void setPosition(Vector2i position);
	LTexture& getTexture();
	string& getCurrentString();
	bool isActive();
	void render();
};

