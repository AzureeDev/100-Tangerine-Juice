#include "PlayerPersistentData.h"
#include "SaveManager.h"

PlayerPersistentData::PlayerPersistentData()
{
	// Init Save Keys

	this->set("account.playerName", "", true);
	this->set("account.playerUnit", "suguri", true);
	this->set("account.playerLevel", "1", true);
	this->set("account.playerExperience", "0", true);
	this->set("account.playerStars", "0", true);
}

map<string, string> PlayerPersistentData::table()
{
	return this->data;
}

string PlayerPersistentData::get(const string key)
{
	auto it = this->data.find(key);

	if (it != this->data.end())
	{
		return it->second;
	}

	SDL_Log("PlayerPersistentData::get() : Error! The key %s doesn't exist.", key.c_str());

	return "";
}

void PlayerPersistentData::set(const string key, const string value, const bool skipSave)
{
	this->data[key] = value;

	if (!skipSave)
	{
		SaveManager::save(this);
	}
}