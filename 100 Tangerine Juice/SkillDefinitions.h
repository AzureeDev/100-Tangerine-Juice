#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "PlayerUnit.h"

using std::string, std::vector, std::function, std::shared_ptr;

class PlayerUnit;
struct UnitParams;

enum class SkillType {
	Normal,
	Offensive,
	Defensive,
	Boost
};

struct SkillData {
	string skillIdentifier;
	string skillName;
	string skillDescription;
	string skillOwner;
	string skillIconPath;
	bool skillRemoveOnDeath = true;
	SkillType skillType = SkillType::Normal;
	function<void(shared_ptr<PlayerUnit> unit)> skillCallback;
	function<bool(shared_ptr<PlayerUnit> unit)> skillConditionFunction = [](shared_ptr<PlayerUnit> unit) { return true; };
	function<void(shared_ptr<PlayerUnit> unit)> skillEffectEnded = [](shared_ptr<PlayerUnit> unit) {};
	int skillCost = 1;
};

struct SkillDefinitions
{
	static vector<SkillData> def;
	static void createDefinitions();
	static vector<SkillData> getUnitSkills(const string unitIdentifier);
	static SkillData getSkillData(const string skillIdentifier);

private:
	static void appendSkillToUnit();
};
