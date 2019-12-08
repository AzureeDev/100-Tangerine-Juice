#include "CosmeticDefinitions.h"
#include <SDL_log.h>
vector<CosmeticData> CosmeticDefinitions::def = {};

/*
struct CosmeticData
{
	string id;
	string type = "hair"; // available: [hair][clothing]
	vector<string> unitIds = {};
	unsigned cost = 0;
	unsigned levelUnlock = 1;
};
*/
void CosmeticDefinitions::createDefinitions()
{
	CosmeticDefinitions::def = {
		{
			"silver",
			"hair",
			"sora",
			450,
			1
		},
		{
			"green",
			"hair",
			"sora",
			600,
			1
		},
		{
			"red_sun",
			"hair",
			"sora",
			1500,
			1
		},
		{
			"lilac",
			"hair",
			"sora",
			3400,
			1
		},
		{
			"fire_ice",
			"hair",
			"sora",
			5000,
			1
		},
		{
			"golden",
			"hair",
			"sora",
			10000,
			1
		},
		{
			"lilac_gold",
			"hair",
			"sora",
			10000,
			1
		},
		{
			"cosmic",
			"hair",
			"sora",
			50000,
			1
		},
	};
}

CosmeticData CosmeticDefinitions::getCosmeticData(const string cosmeticIdentifier)
{
	for (const auto& cosmetic : CosmeticDefinitions::def)
	{
		if (cosmetic.id == cosmeticIdentifier)
		{
			return cosmetic;
		}
	}

	SDL_Log("CosmeticDefinitions::getCosmeticData() : No cosmetic found with the id %s", cosmeticIdentifier.c_str());

	return {};
}

vector<CosmeticData> CosmeticDefinitions::getAllHairs()
{
	vector<CosmeticData> container = {};

	for (const auto& cosmetic : CosmeticDefinitions::def)
	{
		if (cosmetic.type == "hair")
		{
			container.push_back(cosmetic);
		}
	}

	return container;
}
