#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

struct UnitParams 
{
	string unitId;
	string unitName;
	string unitDesc;
	string unitDefaultPose;
	int unitMaxHealth;
	vector<int> unitStats;
};

struct UnitDefinitions
{
	static vector<UnitParams> def;
	static UnitParams getParamsById(const string unitIdentifier);
};

