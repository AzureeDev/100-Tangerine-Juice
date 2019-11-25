#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

struct UnitParams
{
	enum class UnitStatistics {
		Attack,
		Defense,
		Evasion,
		Recovery,
		SkillPowerStart,
		SkillPowerMax
	};

	string unitId;
	string unitName;
	string unitDesc;
	string unitDefaultPose;
	int unitMaxHealth = 5;
	vector<int> unitStats;
};

struct UnitDefinitions
{
	static vector<UnitParams> def;
	static UnitParams getParamsById(const string unitIdentifier);
};
