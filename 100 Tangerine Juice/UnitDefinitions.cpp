#include "UnitDefinitions.h"

vector<UnitParams> UnitDefinitions::def = {
	/*
		Unit ID
		Unit Name
		Unit card desc
		Default Pose
		Max Health
		Vector unit stats
	*/
	{
		"suguri",
		"Suguri",
		"Suguri is a high-risk, high-reward unit. She's able to gather more stars from Bonus panels, and have decent battle stats. Beware, loosing in battles could cost you the victory.",
		"std",
		4,
		{ 1, -1, 2, 5, 1, 4 }
	},
	{ 
		"sora",
		"Sora",
		"Sora is a balanced unit. Her skills are often relying on boosting her own stats rather speeding up through the end of the Road.",
		"std", 
		5, 
		{ 1, 0, 1, 5, 1, 4 }
	},
	{ 
		"sora_m", 
		"Sora (Military)", 
		"Sora, in her Military variant, is more focused on combat, and the ability to pursue other units, in order to bring them down.",
		"std", 
		4, 
		{ 1, 0, 1, 6, 1, 4 }
	},
	{
		"hime",
		"Hime",
		"Hime is having the same passive as Suguri, which means she gather more stars from Bonus panels. Her battle stats are lowered though, making her less effective in battles.",
		"std",
		5,
		{ 1, -1, 0, 5, 0, 4 }
	},
	{ 
		"sham", 
		"Sham",
		"Sham is more focused on defensive aspects in order to survive longer. She won't make miracles in terms of attack power though.",
		"std", 
		5, 
		{ -1, 2, 1, 4, 0, 3 }
	},
	{
		"tsih",
		"Tsih",
		"Tsih is having the unique ability to have a bonus of 1 on her movement roll. Her skills are about survivability.",
		"std",
		4,
		{ 0, 0, 2, 6, 2, 6 }
	},
	{
		"saki",
		"Saki",
		"Saki heals herself by 1 HP at the beginning of her turns. She won't be very effective in battles.",
		"std",
		4,
		{ -1, 0, 1, 5, 0, 4 }
	},
	{ 
		"sb",
		"Star Breaker",
		"Star Breaker is focused on pure damage. Her insane stats allows her to put down any other unit easily. She cannot count on stars though, as she cannot gather them.",
		"std", 
		5, 
		{ 2, 0, -1, 7, 2, 8 }
	},
};

UnitParams UnitDefinitions::getParamsById(const string unitIdentifier)
{
	for (const auto& unit : UnitDefinitions::def)
	{
		if (unit.unitId == unitIdentifier)
		{
			return unit;
		}
	}

	return {};
}
