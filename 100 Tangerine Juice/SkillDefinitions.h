#pragma once
#include <string>
#include <vector>
#include <functional>
#include "PlayerUnit.h"

using std::string, std::vector, std::function;

class PlayerUnit;
struct UnitParams;

struct SkillData {
	string skillIdentifier;
	string skillName;
	string skillDescription;
	string skillOwner;
	string skillIconPath;
	function<void(PlayerUnit* sender, PlayerUnit* receiver)> skillCallback;
	int skillCost = 1;
	bool skillUsableOutsideBattle = true;
	bool skillUsableInsideBattle = false;
};

struct SkillDefinitions
{
	static vector<SkillData> def;
	static void createDefinitions();

private:
	static void appendSkillToUnit();
};
