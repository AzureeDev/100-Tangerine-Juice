#include "CosmeticDefinitions.h"
#include <SDL_log.h>
vector<CosmeticData> CosmeticDefinitions::def = {};

void CosmeticDefinitions::createDefinitions()
{
	CosmeticDefinitions::def = {
		{
			"hair_blue"
		}
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
