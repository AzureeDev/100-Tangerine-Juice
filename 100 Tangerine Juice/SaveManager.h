#pragma once
#include <fstream>
#include <string>
#include <memory>
#include "PlayerPersistentData.h"

using std::string, std::ofstream, std::ifstream, std::shared_ptr;

class SaveManager
{
public:
	static void init(shared_ptr<PlayerPersistentData>& persistData);
	static void load(ifstream& stream, shared_ptr<PlayerPersistentData>& persistData);
	static void save(PlayerPersistentData* data);
};
