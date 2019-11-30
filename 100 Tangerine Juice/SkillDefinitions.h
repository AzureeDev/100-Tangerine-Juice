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
	SkillType skillType = SkillType::Normal;
	function<void(shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)> skillCallback;
	int skillCost = 1;
	bool skillUsableOutsideBattle = true;
	bool skillUsableInsideBattle = false;
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
