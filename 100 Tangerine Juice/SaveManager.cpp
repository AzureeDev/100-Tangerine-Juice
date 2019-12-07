#include "SaveManager.h"
#define NOMINMAX
#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include "json.hpp"

using nlohmann::json;
const string PLAYER_SAVE_FILE_PATH = "data/player_progression.lsav";

void SaveManager::init(shared_ptr<PlayerPersistentData>& persistData)
{
	ifstream playerSave(PLAYER_SAVE_FILE_PATH);

	if (playerSave.is_open()) // File exists
	{
		SaveManager::load(playerSave, persistData); // Load the existing data in our persist
		SaveManager::save(persistData.get()); // Then save it directly after, in order to create missing keys that could be added in the future.
		playerSave.close();
		SDL_Log("Loaded player data.");
	}
	else
	{
		system("mkdir data");
		ofstream newPlayerSave(PLAYER_SAVE_FILE_PATH); // File doesn't exist, so we create a new one.
		SaveManager::save(persistData.get());
		newPlayerSave.close();
		SDL_Log("Couldn't find the save file... Creating a new one");
	}
}

void SaveManager::load(ifstream& stream, shared_ptr<PlayerPersistentData>& persistData)
{
	json data;
	stream >> data;

	if (!data.is_null())
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			persistData->set(it.key(), it.value(), true);
		}
	}
}

void SaveManager::save(PlayerPersistentData* data)
{
	ofstream save(PLAYER_SAVE_FILE_PATH);
	json saveData;

	for (auto& it : data->table())
	{
		saveData[it.first] = it.second;
	}

	save << saveData.dump(4) << std::endl;
	save.close();
}