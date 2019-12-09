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
		/* Hair */
		{ "silver", "Silver", "hair", "sora", 450, 1 },
		{ "green", "Forest Green", "hair", "sora", 600, 1 },
		{ "red_sun", "Red Sun", "hair", "sora", 1500, 1 },
		{ "lilac", "Lilac", "hair", "sora", 3400, 1 },
		{ "fire_ice", "Fire & Ice", "hair", "sora", 5000, 1 },
		{ "golden", "Golden", "hair", "sora", 10000, 1 },
		{ "lilac_gold", "Golden Lilac", "hair", "sora", 10000, 1 },
		{ "cosmic", "Cosmic", "hair", "sora", 50000, 1 },

		{ "citron", "Citron", "hair", "sham", 1000, 1 },
		{ "ice", "Ice", "hair", "sham", 1200, 1 },
		{ "ocean", "Ocean Blue", "hair", "sham", 2500, 1 },
		{ "fushia", "Fushia", "hair", "sham", 5000, 1 },
		{ "golden", "Golden", "hair", "sham", 10000, 1 },


		/* Clothing */

		/* Eye */

		/* Dice */
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
