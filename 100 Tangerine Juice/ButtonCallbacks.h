#pragma once
#include "LClass.h"

class ButtonCallbacks
{
public:
	static void proceedToMainMenu();
	static void quitGame();
	static void mainMenuCredits();
	static void mainMenuUnitDB();
	static void unitDBRequestInfo(const string unitIdentifier);
	static void backToMainMenu();
};

