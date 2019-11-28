#include "UnitDefinitions.h"

vector<UnitParams> UnitDefinitions::def = {};

void UnitDefinitions::createDefinitions()
{
	// unitStats vector: Attack, Defense, Evasion, Recovery, SkillPowerStart, SkillPowerMax
	UnitParams suguri;
	suguri.unitId = "suguri";
	suguri.unitName = "Suguri";
	suguri.unitDesc = "Suguri is a high-risk, high-reward unit. She's able to gather more stars from Bonus panels, and have decent battle stats. Beware, losing in battles could cost you the victory.";
	suguri.unitMaxHealth = 4;
	suguri.unitStats = { 1, -1, 2, 6, 1, 4 };
	suguri.unitStarBonus = 10;

	UnitParams sora;
	sora.unitId = "sora";
	sora.unitName = "Sora";
	sora.unitDesc = "Sora is a balanced unit. Her skills often rely on boosting her own stats rather than speeding through to the end of the Road.";
	sora.unitMaxHealth = 5;
	sora.unitStats = { 1, 0, 1, 5, 1, 5 };

	UnitParams sora_m;
	sora_m.unitId = "sora_m";
	sora_m.unitName = "Sora (Military)";
	sora_m.unitDesc = "Sora, in her Military variant, is more focused on combat and the ability to pursue other units, in order to bring them down. She won't have any recovery rolls, but she cannot use powerful skills.";
	sora_m.unitMaxHealth = 4;
	sora_m.unitStats = { 1, 0, 1, 0, 1, 2 };

	UnitParams hime;
	hime.unitId = "hime";
	hime.unitName = "Hime";
	hime.unitDesc = "Hime has the same passive as Suguri, which means she gather more stars from Bonus panels. Her battle stats are lowered though, making her less effective in battles.";
	hime.unitMaxHealth = 5;
	hime.unitStats = { 1, -1, 0, 5, 0, 4 };
	hime.unitStarBonus = 10;

	UnitParams sham;
	sham.unitId = "sham";
	sham.unitName = "Sham";
	sham.unitDesc = "Sham is more focused on defensive aspects in order to survive longer. She won't make miracles in terms of attack power though.";
	sham.unitMaxHealth = 5;
	sham.unitStats = { 0, 2, 0, 4, 0, 3 };

	UnitParams tsih;
	tsih.unitId = "tsih";
	tsih.unitName = "Tsih";
	tsih.unitDesc = "Tsih has the unique ability to have a bonus of 1 on her movement roll. Her skills are about survivability.";
	tsih.unitMaxHealth = 4;
	tsih.unitStats = { 0, 0, 2, 6, 2, 6 };
	tsih.unitMovementBonus = 1;

	UnitParams saki;
	saki.unitId = "saki";
	saki.unitName = "Saki";
	saki.unitDesc = "Saki is the kind of unit that will want to avoid Encounter panels. She can heal herself by 1 HP at the beginning of her turns, but her battle statistics aren't great.";
	saki.unitMaxHealth = 4;
	saki.unitStats = { -1, 0, 1, 5, 0, 3 };
	saki.unitHealPerTurn = true;

	UnitParams sb;
	sb.unitId = "sb";
	sb.unitName = "Star Breaker";
	sb.unitDesc = "Star Breaker is focused on pure damage. Her insane stats allows her to put down any other unit easily, but her wins won't make other units lose stars.";
	sb.unitMaxHealth = 5;
	sb.unitStats = { 2, 0, -1, 8, 0, 8 };

	UnitDefinitions::def.push_back(suguri);
	UnitDefinitions::def.push_back(sora);
	UnitDefinitions::def.push_back(sora_m);
	UnitDefinitions::def.push_back(hime);
	UnitDefinitions::def.push_back(sham);
	UnitDefinitions::def.push_back(tsih);
	UnitDefinitions::def.push_back(saki);
	UnitDefinitions::def.push_back(sb);
}

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