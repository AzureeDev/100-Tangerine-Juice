#pragma once
#include <SDL.h>
#include <map>
#include <string>

using std::map;
using std::string;

class PlayerPersistentData
{
private:
	map<string, string> data;

public:
	PlayerPersistentData();
	map<string, string> table();
	string get(const string key);
	void set(const string key, const string value, const bool skipSave = false);
};