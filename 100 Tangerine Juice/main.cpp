#include <iostream>
#include "LilacEngine.h"

int main(int argc, char* argv[])
{
	// Entry point
	std::cout << "Initializing..." << std::endl;

	// Engine launch
	LilacEngine gameEngine;
	gameEngine.init();

	// After Quit
	std::cout << "Program ended." << std::endl;
	return 0;
}